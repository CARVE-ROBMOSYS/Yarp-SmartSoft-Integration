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

    virtual ~SendPatternClient()
    {
        m_port.interrupt();
        m_port.close();
    }

    SendPatternClient(const std::string& portName) throw(SmartACE::SmartError)
    {
        if(!yarp::os::Network::checkNetwork() || portName.size()==0 || !m_port.open(portName))
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (sendClient): ERROR: unable to open YARP port"));
        }
        // the send pattern is one-directional
        m_port.setWriteOnly();
        // the client doesn't wait the answer from the server
        m_port.enableBackgroundWrite(true);
    }

    Smart::StatusCode connect(const std::string& server, const std::string& service) throw()
    {
        //FIXME: use it
        YARP_UNUSED(service);
        if (!yarp::os::Network::connect(m_port.getName(), server))
        {
            yError()<<"SendClient: unable to connect to the SendServer:"<<server;
            return Smart::SMART_ERROR;
            //throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (sendClient): ERROR: unable to connect with the server %s"),server);
        }
        else
        {
            server = m_serverName;
            return Smart::SMART_OK;
        }

    }

    Smart::StatusCode disconnect() throw()
    {
        if (!yarp::os::Network::disconnect(m_port.getName(), m_serverName))
        {
            yError()<<"SendClient: unable to disconnect from the SendServer:"<<m_serverName;
            return Smart::SMART_ERROR;
            //throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (sendClient): ERROR: unable to connect with the server %s"),server);
        }
        else
        {
            return Smart::SMART_OK;
        }
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
    yarp::os::Port m_port;
    std::string m_serverName;// FIXME initialization missing

};

} // namespace smartsoft
} // namespace yarp
#endif // YARP_SMARTSOFT_SENDPATTERNCLIENT_H
