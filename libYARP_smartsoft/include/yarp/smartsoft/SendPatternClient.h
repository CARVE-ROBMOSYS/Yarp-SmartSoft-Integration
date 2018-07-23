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
#include <yarp/smartsoft/PatternClientBase.h>

#include <aceSmartSoft.hh>

namespace yarp {
namespace smartsoft {
// FIXME: in the signature of the functions are missing all the SmartComponent* and WiringSlave
// No idea how to use them...
template <class T>
/**
 * @brief The SendPatternClient class
 */
class SendPatternClient : public yarp::smartsoft::PatternClientBase
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

    /**
     * @brief SendPatternClient
     * @param portName
     * @param srvName
     * @param service
     */
    SendPatternClient(const std::string& portName,const std::string& srvName="",
                      const std::string& service="") throw(SmartACE::SmartError)
    {
        //FIXME use it!
        YARP_UNUSED(service);
        m_port = new yarp::os::Port();
        if (!yarp::os::Network::checkNetwork() || portName.empty() || !m_port->open(portName))
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,
                                       "CommPattern (sendClient): ERROR: unable to open YARP port"));
        }
        // the send pattern is one-directional
        m_port->setWriteOnly();
        // the client doesn't wait the answer from the server
        m_port->enableBackgroundWrite(true);
        if (!srvName.empty())
        {
            if (!yarp::os::Network::connect(m_port->getName(), srvName))
            {
                throw(SmartACE::SmartError(Smart::SMART_ERROR,
                                           "CommPattern (sendClient): ERROR: unable to connect to "+srvName));
            }
            m_serverNames.emplace_back(srvName);
        }
    }

    virtual ~SendPatternClient() throw()
    {
        this->disconnect();
        this->remove();
        if (m_port)
        {
            delete m_port;
        }
    }



    Smart::StatusCode blocking(const bool flag) throw() override
    {
        YARP_UNUSED(flag);
        // their code is exactly this one
        return Smart::SMART_OK;
    }

    /**
     * @brief send
     * @param data
     * @return
     */
    Smart::StatusCode send(const T& data) throw()
    {
        if (!m_port)
            return Smart::SMART_ERROR;

        if (m_port->getOutputCount() == 0)
        {
            yError()<<"SendClient: No outgoing connection";
            return Smart::SMART_DISCONNECTED;
        }

        if (!m_port->write(data))
        {
            yError()<<"SendClient: unable to send the data";
            return Smart::SMART_ERROR_COMMUNICATION;
        }

        return Smart::SMART_OK;
    }

};

} // namespace smartsoft
} // namespace yarp
#endif // YARP_SMARTSOFT_SENDPATTERNCLIENT_H
