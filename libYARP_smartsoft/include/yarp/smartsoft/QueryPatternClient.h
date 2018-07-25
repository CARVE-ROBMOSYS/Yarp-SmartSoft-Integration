/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SMARTSOFT_QUERYPATTERNCLIENT_H
#define YARP_SMARTSOFT_QUERYPATTERNCLIENT_H

#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>
#include <yarp/os/PortablePair.h>
#include <yarp/os/RpcClient.h>

#include <yarp/smartsoft/PatternClientBase.h>
#include <yarp/smartsoft/SmartVocabs.h>

#include <aceSmartSoft.hh>

#include <atomic>
#include <mutex>

namespace yarp {
namespace smartsoft {

/**
 * @brief The QueryPatternClient class
 */
template<class R, class A>
class QueryPatternClient : public PatternClientBase,
                           public yarp::os::PortReader
{
public:
    QueryPatternClient() = delete;

    QueryPatternClient(const QueryPatternClient& rhs) = delete;

    /**
     * @brief QueryPatternClient
     * @param portName
     * @param srvName
     * @param service
     */
    QueryPatternClient(const std::string& portName, const std::string& srvName ="",
                       const std::string& service = "") throw(SmartACE::SmartError)
    {
        YARP_UNUSED(service);//FIXME: use it!

        m_port = new yarp::os::Port();
        if (!yarp::os::Network::checkNetwork() || portName.empty() || !m_port || !m_port->open(portName))
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,
                                       "CommPattern (queryClient): ERROR: unable to open YARP port"));
        }

        if (!srvName.empty())
        {
            if (!yarp::os::Network::connect(m_port->getName(), srvName))
            {
                throw(SmartACE::SmartError(Smart::SMART_ERROR,
                                           "CommPattern (QueryClient): ERROR: unable to connect to "+srvName));
            }
            m_serverNames.emplace_back(srvName);
        }
        m_port->setReader(*this);
    }

    /**
     * @brief ~QueryPatternClient
     */
    virtual ~QueryPatternClient() throw()
    {
        this->disconnect();
        this->remove();
        if (m_port)
        {
            delete m_port;
        }
    }

    /**
     * @brief blocking
     * @param flag
     * @return
     */
    Smart::StatusCode blocking(const bool flag) throw() override
    {
        YARP_UNUSED(flag);
        // FIXME: No idea what to do here...
        return Smart::SMART_OK;
    }

    /**
     * @brief query
     * @param request
     * @param answer
     * @return
     */
    Smart::StatusCode query(const R& request, A& answer) throw()
    {

        if (!checkConnection())
        {
            return Smart::SMART_DISCONNECTED;
        }

        uint32_t idReq = sendRequest(request);

        if (idReq == vocab_query_wrong_id)
        {
            yError()<<"QueryClient: error contacting the QueryServer";
            return Smart::SMART_ERROR_COMMUNICATION;
        }
        return fetchAnswer(idReq, answer);
    }

    /**
     * @brief queryRequest
     * @param request
     * @param id
     * @return
     */
    Smart::StatusCode queryRequest(const R& request, uint32_t& id) throw()
    {
        if (!checkConnection())
        {
            return Smart::SMART_DISCONNECTED;
        }

        uint32_t idReq = sendRequest(request);
        // I expect that the server answer me with the ticket generated
        if (idReq == vocab_query_wrong_id)
        {
            yError()<<"QueryClient: error contacting the QueryServer";
            return Smart::SMART_ERROR_COMMUNICATION;
        }
        id = idReq;
        return Smart::SMART_OK;
    }

    /**
     * @brief queryReceive
     * @param id
     * @param answer
     * @return
     */
    Smart::StatusCode queryReceive(const uint32_t& id, A& answer) throw()
    {
        if (!checkConnection())
        {
            return Smart::SMART_DISCONNECTED;
        }

        std::lock_guard<std::mutex> lk_guard(m_map_mutex);
        if (m_map_req.find(id) == m_map_req.end())
        {
            yError()<<"QueryClient: requested id"<<id<<"not valid..";
            return Smart::SMART_WRONGID;
        }

        if (m_map_req[id].__isReady)
        {
            answer = m_map_req[id].__answer;
            return Smart::SMART_OK;
        }
        else
        {
            return Smart::SMART_NODATA;
        }
    }

    /**
     * @brief queryReceiveWait
     * @param id
     * @param answer
     * @param timeout
     * @return
     */
    Smart::StatusCode queryReceiveWait(const uint32_t& id, A& answer, const std::chrono::steady_clock::duration &timeout=std::chrono::steady_clock::duration::zero()) throw()
    {
        if (!checkConnection())
        {
            return Smart::SMART_DISCONNECTED;
        }

        if (m_map_req.find(id) == m_map_req.end())
        {
            yError()<<"QueryClient: requested id"<<id<<"not valid..";
            return Smart::SMART_WRONGID;
        }
        return fetchAnswer(id, answer, timeout);
    }

    /**
     * @brief queryDiscard
     * @param id
     * @return
     */
    Smart::StatusCode queryDiscard(const uint32_t& id) throw()
    {
        std::lock_guard<std::mutex> lk_guard(m_map_mutex);
        if (m_map_req.find(id) == m_map_req.end())
        {
            yError()<<"QueryClient: requested id"<<id<<"not valid..";
            return Smart::SMART_WRONGID;
        }
        m_map_req.erase(id);
        return Smart::SMART_OK;
    }

protected:
    virtual bool read(yarp::os::ConnectionReader& reader) override
    {
        if (reader.expectInt32() == vocab_query_id)
        {
            uint32_t _id = reader.expectInt32();
            std::lock_guard<std::mutex> lk_guard(m_map_mutex);
            if (m_map_req.find(_id) == m_map_req.end())
            {
                yError()<<"QueryClient: requested id"<<_id<<"not valid, the request has been discarded";
                return false;
            }
            bool ok = m_map_req[_id].__answer.read(reader);
            if (!ok)
            {
                return false;
            }
            m_map_req[_id].__isReady = true;
            m_map_req[_id].__cv.notify_all();
            return true;
        }
        return false;
    }

private:
    struct QueryRequest
    {
        A __answer;
        bool __isReady;
        std::condition_variable __cv;
        QueryRequest(bool isReady=false) : __isReady(isReady)
        {}
    };
    bool checkConnection()
    {
        if (!m_port || m_port->getOutputCount() == 0)
        {
            yError()<<"QueryClient: no outgoing connections..";
            return false;
        }
        return true;
    }

    u_int32_t sendRequest(const R& request)
    {
        u_int32_t idReq = m_num_req++;

        yarp::os::PortablePair<yarp::os::Bottle, const R&> message;
        message.head.addInt32(yarp::os::Value(vocab_query_id));
        message.head.addInt32(yarp::os::Value(m_num_req));
        message.body = request;

        bool ok = (m_port && m_port->write(message));
        if (ok)
        {
            std::lock_guard<std::mutex> lk_guard(m_map_mutex);
            m_map_req[m_num_req] = QueryRequest();
        }
        return ok ? idReq : vocab_query_wrong_id;
    }

    Smart::StatusCode fetchAnswer(const uint32_t& idReq, A& answer, const std::chrono::steady_clock::duration &timeout=std::chrono::steady_clock::duration::zero())
    {
        std::lock_guard<std::mutex> lk_guard(m_map_mutex);
        bool ok = true;
        if (!m_map_req.at(idReq).__isReady)
        {
            std::unique_lock<std::mutex> uniqueLk(m_cv_mutex);
            // We need this lambda in the wait to avoid spurious wake up
            if (timeout == std::chrono::steady_clock::duration::zero())
            {
                // Wait forever
                m_map_req[idReq].__cv.wait(uniqueLk, [this, idReq] { return m_map_req[idReq].__isReady; });
            }
            else
            {
                ok = m_map_req[idReq].__cv.wait_for(uniqueLk, timeout, [this, idReq] { return m_map_req[idReq].__isReady; });
            }
        }

        if (ok)
        {
            answer = m_map_req[idReq].__answer;
            // Once the answered has been consumed, remove it from the queue.
            m_map_req.erase(idReq);
            return Smart::SMART_OK;
        }
        else
        {
            return  Smart::SMART_ERROR;
        }
    }
    std::map<uint32_t, QueryRequest> m_map_req;
    std::mutex m_map_mutex;
    std::mutex m_cv_mutex;
    std::atomic<uint32_t> m_num_req{0};


};

} // namespace smartsoft
} // namespace yarp

#endif // YARP_SMARTSOFT_QUERYPATTERNCLIENT_H
