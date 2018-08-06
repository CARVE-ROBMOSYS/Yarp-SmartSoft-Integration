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
/**
 * @brief The SendPatternClient class
 */
template <class T>
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
     * @brief SendPatternClient constructor
     * @param portName name of the port associated to the client.
     * @param srvName name of the port of the server that it has to connect to.
     * @param service name of the service.
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
        // their code is exactly this one
        return Smart::SMART_OK;
    }

    /** @brief
     * Perform a one-way communication. Appropriate status codes make
     *  sure that the information has been transferred.
     *
     *  @param c the object to be sent (Communication Object)
     *
     *  @return status code:
     *    - SMART_OK                  : everything is ok and communication object sent to server
     *    - SMART_DISCONNECTED        : the client is disconnected and no send can be made
     *    - SMART_ERROR_COMMUNICATION : communication problems, data not transmitted
     *    - SMART_ERROR               : something went wrong, data not transmitted
     */
    Smart::StatusCode send(const T& data) throw()
    {
        if (!m_port)
            return Smart::SMART_ERROR;

        if (m_port->getOutputCount() == 0)
        {
            return Smart::SMART_DISCONNECTED;
        }

        if (!m_port->write(data))
        {
            return Smart::SMART_ERROR_COMMUNICATION;
        }

        return Smart::SMART_OK;
    }

};

} // namespace smartsoft
} // namespace yarp
#endif // YARP_SMARTSOFT_SENDPATTERNCLIENT_H
