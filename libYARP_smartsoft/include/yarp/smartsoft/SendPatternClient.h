/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SMARTSOFT_SENDPATTERNCLIENT_H
#define YARP_SMARTSOFT_SENDPATTERNCLIENT_H

#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>

#include <aceSmartSoft.hh>

namespace yarp {
namespace smartsoft {
// FIXME: in the signature of the functions are missing all the SmartComponent* and WiringSlave
// No idea how to use them...
template <class T>
/**
 * @brief The SendPatternClient class
 */
class SendPatternClient //: public SmartACE::SendClient<T> FIXME: we need this inheritance??
{
public:
    /**
     * @brief SendPatternClient, default constructor deleted
     */
    SendPatternClient() = delete;

    /**
     * @brief copy constructor deleted
     */
    SendPatternClient(const SendPatternClient& rhs) = delete;

    virtual ~SendPatternClient() throw()
    {
        disconnect();
        remove();
    }

    SendPatternClient(const std::string& portName,const std::string& srvName="", const std::string& service="") throw(SmartACE::SmartError)
    {
        //FIXME use it!
        YARP_UNUSED(service);
        if(!yarp::os::Network::checkNetwork() || portName.empty() || !m_port.open(portName))
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (sendClient): ERROR: unable to open YARP port"));
        }
        // the send pattern is one-directional
        m_port.setWriteOnly();
        // the client doesn't wait the answer from the server
        m_port.enableBackgroundWrite(true);
        if (!srvName.empty())
        {
            if (!yarp::os::Network::connect(m_port.getName(), srvName))
            {
                throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (sendClient): ERROR: unable to connect to "+srvName));
            }
            m_serverNames.emplace_back(srvName);
        }
    }

    Smart::StatusCode add(const std::string& portName) throw()
    {
        bool ok = true;
        if (yarp::os::Network::exists(portName))
        {
            return Smart::SMART_PORTALREADYUSED;
        }
        if (m_port.isOpen())
        {
            m_port.interrupt();
            m_port.close();
        }

        if (m_port.open(portName))
        {
            // the name of the port is changed, but old connection has to be restored
            // FIXME: am I right??
            ok = connectAllSrv();
        }
        else
        {
            ok = false;
        }

        return ok ? Smart::SMART_OK : Smart::SMART_ERROR;
    }

    Smart::StatusCode remove() throw()
    {
        // FIXME: how do we maintain the connections without the port???
        m_port.interrupt();
        m_port.close();
        return Smart::SMART_OK;
    }

    Smart::StatusCode connect(const std::string& server, const std::string& service="") throw()
    {
        //FIXME: use it
        YARP_UNUSED(service);
        if (!yarp::os::Network::connect(m_port.getName(), server))
        {
            yError()<<"SendClient: unable to connect to the SendServer:"<<server;
            return Smart::SMART_ERROR;
        }
        else
        {
            m_serverNames.emplace_back(server);
            return Smart::SMART_OK;
        }

    }

    Smart::StatusCode disconnect() throw()
    {
        bool ok = disconnectAllSrv();
        m_serverNames.clear();
        return ok ? Smart::SMART_OK : Smart::SMART_ERROR;
    }

    Smart::StatusCode blocking(const bool flag) throw()
    {
        YARP_UNUSED(flag);
        // their code is exactly this one
        return Smart::SMART_OK;
    }

    Smart::StatusCode send(const T& data) throw()
    {
        if (m_port.getOutputCount() == 0)
        {
            yError()<<"SendClient: No outgoing connection";
            return Smart::SMART_DISCONNECTED;
        }

        if (!m_port.write(data))
        {
            yError()<<"SendClient: unable to send the data";
            return Smart::SMART_ERROR_COMMUNICATION;
        }

        return Smart::SMART_OK;
    }


private:
    bool disconnectAllSrv()
    {
        bool ok = true;
        for (auto srvName : m_serverNames) {
            if (!yarp::os::Network::disconnect(m_port.getName(), srvName))
            {
                yError()<<"SendClient: unable to disconnect from the SendServer:"<<srvName;
                ok = false;
            }
        }
        return ok;
    }

    bool connectAllSrv()
    {
        bool ok = true;
        for (auto srvName : m_serverNames) {
            if (!yarp::os::Network::connect(m_port.getName(), srvName))
            {
                yError()<<"SendClient: unable to connect to the SendServer:"<<srvName;
                ok = false;
            }
        }
        return ok;
    }
    yarp::os::Port m_port;
    std::vector<std::string> m_serverNames;// FIXME initialization missing

};

} // namespace smartsoft
} // namespace yarp
#endif // YARP_SMARTSOFT_SENDPATTERNCLIENT_H
