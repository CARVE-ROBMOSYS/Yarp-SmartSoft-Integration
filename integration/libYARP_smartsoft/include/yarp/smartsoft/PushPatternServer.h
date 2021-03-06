/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SMARTSOFT_PUSHPATTERNSERVER_H
#define YARP_SMARTSOFT_PUSHPATTERNSERVER_H

#include <yarp/os/BufferedPort.h>
#include <yarp/os/Network.h>

#include <aceSmartSoft.hh>

namespace yarp {
namespace smartsoft {
/**
 * @brief The PushPatternServer class
 */
template <class T>
class PushPatternServer
{
public:
    PushPatternServer() = delete;
    /**
     * @brief PushPatternServer constructor
     * @param portName, name of the port associate to this server.
     * @param service, name of the service
     */
    PushPatternServer(const std::string portName, const std::string& service = "") throw(SmartACE::SmartError)
    {
        // FIXME: USE IT!
        YARP_UNUSED(service);
        if (!yarp::os::Network::checkNetwork() || portName.empty() || !m_port.open(portName))
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (sendServer): ERROR: unable to open YARP port"));
        }
        // The server can only receive.
        m_port.setWriteOnly();
    }

    virtual ~PushPatternServer() throw()
    {
        m_port.interrupt();
        m_port.close();
    }

    /** @brief
     * Provide new data which is sent to all subscribed clients
     *
     *  PushHandler::handlePushRequest() directly or indirectly
     *  use this method to provide new data.
     *
     *  @param d contains the newly acquired data to be sent as
     *           update.
     *
     *  @return status code
     *    - SMART_OK                  : everything is ok
     */
    Smart::StatusCode put(const T& d) throw()
    {
        m_port.prepare() = d;
        m_port.write();
        return Smart::SMART_OK;
    }
private:
    yarp::os::BufferedPort<T> m_port;
};

} // namespace smartsoft
} // namespace yarp


#endif // YARP_SMARTSOFT_PUSHPATTERNSERVER_H
