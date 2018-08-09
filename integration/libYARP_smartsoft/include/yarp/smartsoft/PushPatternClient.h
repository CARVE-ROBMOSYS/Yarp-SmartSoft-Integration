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
     * @brief PushPatternClient constructor
     * @param portName name of the port associated to the client
     * @param srvName name of the port of the server that it has to connect to
     * @param service name of the service.
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
        m_blocking = flag;
        return Smart::SMART_OK;
    }

    /** @brief
     * Connect this service requestor to the denoted service provider. An
     *  already established connection is first disconnected. See disconnect()
     *  for implications on running or pending queries in that case.
     *
     *  @param server   name of the server
     *  @param service  name of the service
     *
     *  @return status code
     *   - SMART_OK                  : everything is OK and connected to the specified service.
     *   - SMART_ERROR               : something went wrong, service requestor is now not connected to any
     *                                 service provider.
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


    /** @brief
     * Subscribe at the server to periodically get every n-th update. A
     *  newly subscribed client gets the next available new data and is
     *  then updated with regard to its individual update cycle.
     *
     *  @return status code
     *    - SMART_OK                  : everything is ok and client is subscribed
     *    - SMART_DISCONNECTED        : client is not connected to a server and can therefore
     *                                  not subscribe for updates, not subscribed
     *    - SMART_ERROR_COMMUNICATION : communication problems, not subscribed
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

    /** @brief
     * Unsubscribe to get no more updates. All blocking calls are aborted with the appropriate
     *  status and yet received and still buffered data is deleted to avoid returning old data.
     *
     *  @return status code
     *    - SMART_OK                  : everything is ok and client is now unsubscribed or
     *                                  has already been unsubscribed
     *    - SMART_ERROR_COMMUNICATION : communication problems, not unsubscribed
     *    - SMART_ERROR               : something went wrong, not unsubscribed
     *
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

    /** @brief
     * Non-blocking call to immediately return the latest available
     *  data buffered at the client side from the most recent update.
     *
     *  No data is returned as long as no update is received since
     *  subscription. To avoid returning old data, no data is
     *  returned after the client is unsubscribed or when the
     *  server is not active.
     *
     * @param d is set to the newest currently available data
     *
     * @return status code
     *   - SMART_OK                  : everything ok and latest data since client got subscribed
     *                                 is returned.
     *   - SMART_NODATA              : client has not yet received an update since subscription and
     *                                 therefore no data is available and no data is returned.
     *   - SMART_NOTACTIVATED        : the server is currently not active and does therefore not
     *                                 provide updates at the expected rate. No valid data returned.
     *   - SMART_UNSUBSCRIBED        : no data available since client is not subscribed and can
     *                                 therefore not receive updates. Method does not return old data from
     *                                 last subscription since these might be based on too old parameter
     *                                 settings. To get data one has to be subscribed.
     *   - SMART_DISCONNECTED        : no data returned since client is even not connected to a server.
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

    /** @brief
     * Blocking call which waits until the next update is received.
     *
     *  @param d is set to the newest currently available data
     *  @param timeout allows to release the blocking wait after a given timeout time (the default max_time means infinite blocking)
     *
     *  @return status code
     *   - SMART_OK                  : everything is ok and just received data is returned.
     *   - SMART_CANCELLED           : blocking is not allowed or is not allowed anymore. Waiting for the
     *                                 next update is aborted and no valid data is returned.
     *   - SMART_UNSUBSCRIBED        : returns immediately without data if the client is not subscribed.
     *   - SMART_DISCONNECTED        : returns immediately without data since client is even not connected
     *                                 to a server.
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

    /** @brief
     * Get cycle time and server state.
     *
     *  Returns cycle time of server in [seconds] and server state indicating
     *  whether server is activated or not. The client can decide on the cycle
     *  time on its individual update rate at subscription.
     *
     * @param t is set to the server cycle time [seconds]
     * @param r indicates whether server is started [true, false]
     *
     * @return status code
     *   - SMART_OK                  : everything is ok and returned values are valid.
     *   - SMART_DISCONNECTED        : client is not connected to a server and
     *                                 therefore not get any valid server info.
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
