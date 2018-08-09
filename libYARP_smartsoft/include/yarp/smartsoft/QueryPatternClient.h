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
#include <future>
#include <thread>
#include <memory>
#include <mutex>

namespace yarp {
namespace smartsoft {

/**
 * @brief The QueryPatternClient class
 */
template<class R, class A>
class QueryPatternClient : public PatternClientBase
                           //public yarp::os::PortReader
{
public:
    QueryPatternClient() = delete;

    QueryPatternClient(const QueryPatternClient& rhs) = delete;

    /**
     * @brief QueryPatternClient constructor
     * @param portName name of the port associated to the client
     * @param srvName name of the port of the server that it has to connect to
     * @param service name of the service.
     */
    QueryPatternClient(const std::string& portName, const std::string& srvName ="",
                       const std::string& service = "") throw(SmartACE::SmartError)
    {
        YARP_UNUSED(service);//FIXME: use it!

        m_port = &m_rpc_client.asPort();
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
    }

    /**
     * @brief ~QueryPatternClient
     */
    virtual ~QueryPatternClient() throw()
    {
        this->disconnect();
        this->remove();
    }

    /**
     * @brief
     * If blocking is set to false all blocking calls return with SMART_CANCELLED. This can be
     * used to abort blocking calls.
     *
     * @param b (blocking)  true/false
     *
     * @return status code
     * - SMART_OK                  : new mode set
     * - SMART_ERROR               : something went wrong
     */
    Smart::StatusCode blocking(const bool flag) throw() override
    {
        YARP_UNUSED(flag);
        // FIXME: No idea what to do here...
        return Smart::SMART_OK;
    }

    /** @brief
     * Blocking Query.
     *
     *  Perform a blocking query and return only when the query answer
     *  is available. Member function is thread safe and thread reentrant.
     *
     *  @param request send this request to the server (Portable)
     *  @param answer  returned answer from the server (Portable)
     *
     *  @return status code:
     *    - SMART_OK                  : everything is ok and <I>answer</I> contains answer
     *    - SMART_CANCELLED           : blocking is not allowed or is not allowed anymore and therefore
     *                                  pending query is aborted, answer is lost and <I>answer</I>
     *                                  contains no valid answer.
     *    - SMART_DISCONNECTED        : the client is either disconnected and no query
     *                                  can be made or it got disconnected and a pending
     *                                  query is aborted without answer. In both cases,
     *                                  <I>answer</I> is not valid.
     *    - SMART_ERROR_COMMUNICATION : communication problems, <I>answer</I> is not valid.
     *    - SMART_ERROR               : something went wrong, <I>answer</I> is not valid.
     */
    Smart::StatusCode query(const R& request, A& answer) throw()
    {

        if (!checkConnection())
        {
            return Smart::SMART_DISCONNECTED;
        }

        std::lock_guard<std::mutex> lk_guard(m_map_mutex);
        uint32_t idReq = sendRequest(request);

        if (idReq == vocab_query_wrong_id)
        {
            yError()<<"QueryClient: error contacting the QueryServer";
            return Smart::SMART_ERROR_COMMUNICATION;
        }
        return fetchAnswer(idReq, answer);
    }

    /** @brief
     * Asynchronous Query.
     *
     *  Perform a query and receive the answer later, returns immediately.
     *  Member function is thread safe and reentrant.
     *
     *  @param request send this request to the server (Portable)
     *  @param id      returns the identifier which is later used to receive
     *                 the reply to this request
     *
     *  @return status code:
     *    - SMART_OK                  : everything is ok and <I>id</I> contains query identifier
     *                                  used to either fetch or discard the answer.
     *    - SMART_DISCONNECTED        : request is rejected since client is not connected to a server
     *                                  and therefore <I>id</I> is not a valid identifier.
     *    - SMART_ERROR_COMMUNICATION : communication problems, <I>id</I> is not valid.
     *    - SMART_ERROR               : something went wrong, <I>id</I> is not valid.
     */
    Smart::StatusCode queryRequest(const R& request, uint32_t& id) throw()
    {
        if (!checkConnection())
        {
            return Smart::SMART_DISCONNECTED;
        }

        std::lock_guard<std::mutex> lk_guard(m_map_mutex);
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

    /** @brief
     * Check if answer is available.
     *
     *  Non-blocking call to fetch the answer belonging to the given identifier.
     *  Returns immediately. Member function is thread safe and reentrant.
     *
     *  @warning
     *    It is not allowed to call queryReceive(), queryReceiveWait() or queryDiscard() concurrently
     *    with the <I>same</I> query id (which is not a restriction since it makes no sense !)
     *
     *  @param id      provides the identifier of the query
     *  @param answer  is set to the answer returned from the server if it was available
     *
     *  @return status code:
     *    - SMART_OK           : everything is ok and <I>answer</I> contains the answer
     *    - SMART_WRONGID      : no pending query with this identifier available, therefore no valid
     *                           <I>answer</I> returned.
     *    - SMART_NODATA       : answer not yet available, therefore try again later. The identifier <I>id</I>
     *                           keeps valid, but <I>answer</I> contains no valid answer.
     *    - SMART_DISCONNECTED : the answer belonging to the <I>id</I> can not be received
     *                           anymore since the client got disconnected. <I>id</I> is
     *                           not valid any longer and <I>answer</I> contains no valid answer.
     *    - SMART_ERROR        : something went wrong, <I>answer</I> contains no answer and <I>id</I> is
     *                           not valid any longer.
     *
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
            return Smart::SMART_WRONGID;
        }

        if (fetchAnswer(id,answer,false) == Smart::SMART_OK)
        {
            return Smart::SMART_OK;
        }
        else
        {
            return Smart::SMART_NODATA;
        }
    }

    /** @brief
     * Wait for reply.
     *
     *  Blocking call to fetch the answer belonging to the given identifier. Waits until
     *  the answer is received.
     *
     *  @warning
     *    It is not allowed to call queryReceive(), queryReceiveWait() or queryDiscard() concurrently
     *    with the <I>same</I> query id (which is not a restriction since it makes no sense !)
     *
     *  @param id       provides the identifier of the query
     *  @param answer   is set to the answer returned from the server if it was available
     *
     *  @return status code:
     *    - SMART_OK           : everything is ok and <I>answer</I> contains the answer
     *    - SMART_WRONGID      : no pending query with this identifier available, therefore no
     *                           valid <I>answer</I> returned.
     *    - SMART_CANCELLED    : blocking call is not allowed or is not allowed anymore and therefore
     *                           blocking call is aborted and no valid <I>answer</I> is returned. The
     *                           query identifier <I>id</I> keeps valid and one can either again call
     *                           queryReceive(), queryReceiveWait() or discard the answer by calling
     *                           queryDiscard().
     *    - SMART_DISCONNECTED : blocking call is aborted and the answer belonging to <I>id</I> can not
     *                           be received anymore since client got disconnected. <I>id</I> is not valid
     *                           any longer and <I>answer</I> contains no valid answer.
     *    - SMART_ERROR        : something went wrong, <I>answer</I> contains no answer and <I>id</I> is
     *                           not valid any longer.
     *
     */
    Smart::StatusCode queryReceiveWait(const uint32_t& id, A& answer, const std::chrono::steady_clock::duration &timeout=std::chrono::steady_clock::duration::zero()) throw()
    {
        if (!checkConnection())
        {
            return Smart::SMART_DISCONNECTED;
        }

        std::lock_guard<std::mutex> lk_guard(m_map_mutex);
        if (m_map_req.find(id) == m_map_req.end())
        {
            return Smart::SMART_WRONGID;
        }
        return fetchAnswer(id, answer, false, timeout);
    }

    /**  @brief
     * Discard the pending answer with the identifier <I>id</I>
     *
     *  Call this member function if you do not want to get the answer of a request anymore which
     *  was invoked by queryRequest(). This member function invalidates the identifier <I>id</I>.
     *
     *  @warning
     *    This member function does NOT abort blocking calls ! This is done by the blocking() member
     *    function. It has to be called if you have not yet received an answer and the identifier is
     *    still valid, for example due to a CANCELLED return value, and you don't want to get the
     *    answer anymore.
     *
     *  @warning
     *    It is not allowed to call queryReceive(), queryReceiveWait() or queryDiscard() concurrently
     *    with the <I>same</I> query id (which is not a restriction since it makes no sense !)
     *
     *  @param id  provides the identifier of the query
     *
     *  @return status code:
     *    - SMART_OK           : everything is ok and query with the identifier <I>id</I> discarded.
     *    - SMART_WRONGID      : no pending query with this identifier.
     *    - SMART_ERROR        : something went wrong, <I>id</I> not valid any longer.
     *
     */
    Smart::StatusCode queryDiscard(const uint32_t& id) throw()
    {
        std::lock_guard<std::mutex> lk_guard(m_map_mutex);
        if (m_map_req.find(id) == m_map_req.end())
        {
            return Smart::SMART_WRONGID;
        }
        m_map_req.erase(id);
        return Smart::SMART_OK;
    }

protected:

private:
    struct QueryRequest
    {
        A __answer;
        std::future<bool> __future;
        QueryRequest()
        {}

        QueryRequest(std::future<bool>&& fut) : __future{std::move(fut)}
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
        m_num_req++;
        u_int32_t idReq = m_num_req;

        yarp::os::PortablePair<yarp::os::Bottle, R> message;
        message.head.addInt32(vocab_query_id);
        message.head.addInt32(m_num_req);
        message.body = request;

        m_map_req[m_num_req] = QueryRequest(std::async(std::launch::async,
                                                       [this, message] {
                                                           return m_port->write(message,m_map_req[m_num_req].__answer);
                                                       }
                                                       ));
        return idReq;
    }

    Smart::StatusCode fetchAnswer(const uint32_t& idReq, A& answer, bool waitForever = true, const std::chrono::steady_clock::duration &timeout=std::chrono::steady_clock::duration::zero())
    {
        bool ok = false;
//        yDebug()<<"Waiting... map size:"<<m_map_req.size();
//        yDebug()<<"Fetching..." << idReq << " is valid " << m_map_req.at(idReq).__future.valid();

        if (!waitForever)
        {
            std::future_status s = m_map_req.at(idReq).__future.wait_for(timeout);
            if(s == std::future_status::ready)
            {
                m_map_req.at(idReq).__future.get();
                ok = true;
            }
            else
            {
                return Smart::SMART_NODATA;
            }
        }
        else
        {
            // Wait forever
            m_map_req.at(idReq).__future.get();
            ok = true;
        }

        if (ok)
        {
            answer = m_map_req.at(idReq).__answer;
            // Once the answered has been consumed, remove it from the queue.
            m_map_req.erase(idReq);
            return Smart::SMART_OK;
        }
        else
        {
            return  Smart::SMART_ERROR;
        }
    }

    yarp::os::RpcClient m_rpc_client;
    std::map<uint32_t, QueryRequest> m_map_req;
    std::mutex m_map_mutex;
    std::atomic<uint32_t> m_num_req{0};
};

} // namespace smartsoft
} // namespace yarp

#endif // YARP_SMARTSOFT_QUERYPATTERNCLIENT_H
