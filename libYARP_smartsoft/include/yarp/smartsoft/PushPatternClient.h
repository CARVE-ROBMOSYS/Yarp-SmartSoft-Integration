/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SMARTSOFT_PUSHPATTERNCLIENT_H
#define YARP_SMARTSOFT_PUSHPATTERNCLIENT_H

#include <yarp/os/BufferedPort.h>
#include <yarp/os/Network.h>
#include <yarp/os/Subscriber.h>
#include <yarp/smartsoft/PatternClientBase.h>

#include <future>
#include <mutex>
#include <thread>

namespace yarp {
namespace smartsoft {
/**
 * @brief The PushPatternClient class
 */
template <class T>
class PushPatternClient : public PatternClientBase,
                          public yarp::os::PortReader
{
public:
    /**
     * @brief PushPatternClient, default constructor deleted
     */
    PushPatternClient() = delete;

    /**
     * @brief copy constructor deleted
     */
    PushPatternClient(const PushPatternClient& rhs) = delete;

    /**
     * @brief PushPatternClient
     * @param portName
     * @param srvName
     * @param service
     */
    PushPatternClient(const std::string& portName, const std::string& srvName="",
                      const std::string& service="") throw(SmartACE::SmartError)
    {
        YARP_UNUSED(service);
        m_port = new yarp::os::Port();
        if (!yarp::os::Network::checkNetwork() || portName.empty() || !m_port->open(portName))
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,
                                       "CommPattern (sendClient): ERROR: unable to open YARP port"));
        }
        // the send pattern is one-directional
        m_port->setReadOnly();
        // the client doesn't wait the answer from the server
        //m_port->enableBackgroundWrite(true);
        if (!srvName.empty())
        {
            if (!yarp::os::Network::exists(srvName))
            {
                throw(SmartACE::SmartError(Smart::SMART_ERROR,
                                           "CommPattern (pushClient): ERROR: unable to connect to "+srvName));
            }
            m_serverNames.emplace_back(srvName);
        }
        m_port->setReader(*this);
    }


    virtual ~PushPatternClient() throw()
    {
        this->disconnect();
        this->remove();

        if (m_port)
        {
            delete m_port;
            m_port = nullptr;
        }
    }

    /**
     * @brief blocking
     * @param flag
     * @return
     */
    Smart::StatusCode blocking(const bool flag) throw() override
    {
        m_blocking = flag;
        return Smart::SMART_OK;
    }
    /**
     * @brief connect
     * @param server
     * @param service
     * @return
     */
    Smart::StatusCode connect(const std::string& server, const std::string& service="") throw() override
    {
        if (!m_port)
            return Smart::SMART_ERROR;
        //FIXME: use it
        YARP_UNUSED(service);
        if (!yarp::os::Network::exists(server))
        {
            yError()<<"SendClient: unable to connect to the SendServer:"<<server;
            return Smart::SMART_ERROR;
        }
        else
        {
            m_connected = true;
            m_serverNames.emplace_back(server);
            return Smart::SMART_OK;
        }

    }

    /**
     * @brief subscribe
     * @return
     */
    Smart::StatusCode subscribe() throw()
    {
        m_numRead = 0;
        if (!m_connected)
        {
            yError()<<"PushClient: not connected to the PushServer";
            return Smart::SMART_DISCONNECTED;
        }

        if (!connectAllSrv())
        {
            yError()<<"PushClient: impossible to subscribe";
            return Smart::SMART_ERROR_COMMUNICATION;
        }

        m_subscribed = true;

        return Smart::SMART_OK;
    }

    /**
     * @brief unsubscribe
     * @return
     */
    Smart::StatusCode unsubscribe() throw()
    {
        if (!disconnectAllSrv())
        {
            yError()<<"PushClient: impossible to subscribe";
            return Smart::SMART_ERROR_COMMUNICATION;
        }

        m_subscribed = false;

        return Smart::SMART_OK;
    }

    /**
     * @brief getUpdate
     * @param d
     * @return
     */
    Smart::StatusCode getUpdate(T& d) throw()
    {
        if (!m_connected)
        {
            yError()<<"PushClient: not connected to the PushServer";
            return Smart::SMART_DISCONNECTED;
        }

        if (!m_subscribed)
        {
            yError()<<"PushClient: not subscribed to any server";
            return Smart::SMART_UNSUBSCRIBED;
        }

        if (m_numRead == 0)
        {
            yError()<<"PushClient: no data received since subscription";
            return Smart::SMART_NODATA;
        }
        std::lock_guard<std::mutex> lk(m_mutex_data);
        d = m_last_data;
        return Smart::SMART_OK;
    }

    /**
     * @brief getUpdateWait
     * @param d
     * @param timeout
     * @return
     */
    Smart::StatusCode getUpdateWait(T& d, const std::chrono::steady_clock::duration &timeout=std::chrono::steady_clock::duration::zero()) throw()
    {
        m_isReady = false;
        if (!m_connected)
        {
            yError()<<"PushClient: not connected to the PushServer";
            return Smart::SMART_DISCONNECTED;
        }

        if (!m_subscribed)
        {
            yError()<<"PushClient: not subscribed to any server";
            return Smart::SMART_UNSUBSCRIBED;
        }

        std::unique_lock<std::mutex> lk_cv(m_mutex_cv);
        if (!m_blocking || !cv.wait_for(lk_cv, timeout, [this]{return m_isReady;}))
        {
            yError()<<"PushClient: request cancelled..";
            return Smart::SMART_CANCELLED;
        }
        std::lock_guard<std::mutex> lk(m_mutex_data);
        d = m_last_data;
        return Smart::SMART_OK;
    }

    /**
     * @brief getServerInfo
     * @param t
     * @param r
     * @return
     */
    Smart::StatusCode getServerInfo(double& t,bool& r) throw()
    {
        r = m_connected;
        t = (yarp::os::Time::now() - m_startTime) / m_numRead;
        return m_connected ? Smart::SMART_OK : Smart::SMART_DISCONNECTED;
    }

private:

    virtual bool read(yarp::os::ConnectionReader& reader) override
    {
        if (!m_connected || !m_subscribed)
        {
            return false;
        }
        m_numRead++;
        bool ok = m_curr_data.read(reader);
        if (ok)
        {
            std::lock_guard<std::mutex> lk(m_mutex_data);
            m_last_data = m_curr_data;
            std::unique_lock<std::mutex> lk_cv(m_mutex_cv);
            m_isReady = true;
            cv.notify_one();
        }
        else
        {
            return false;
        }
        return true;
    }

    bool disconnectAllSrv()
    {
        if (!m_port)
            return false;
        bool ok = true;
        for (auto srvName : m_serverNames) {
            if (!yarp::os::Network::disconnect(srvName, m_port->getName()))
            {
                yError()<<"SendClient: unable to disconnect from the SendServer:"<<srvName;
                ok = false;
            }
        }
        return ok;
    }

    bool connectAllSrv()
    {
        if (!m_port)
            return false;
        bool ok = true;
        for (auto srvName : m_serverNames) {
            if (!yarp::os::Network::connect(srvName, m_port->getName()))
            {
                yError()<<"SendClient: unable to connect to the SendServer:"<<srvName;
                ok = false;
            }
        }
        return ok;
    }

    T m_last_data;
    T m_curr_data;
    bool m_connected{false};
    bool m_subscribed{false};
    bool m_isReady{false};
    std::atomic_bool m_blocking{true};
    std::atomic_int m_numRead{0};
    std::mutex m_mutex_data;
    std::mutex m_mutex_cv;
    std::condition_variable cv;
    double m_startTime{yarp::os::Time::now()};

};

} // namespace smartsoft
} // namespace yarp

#endif // YARP_SMARTSOFT_PUSHPATTERNCLIENT_H
