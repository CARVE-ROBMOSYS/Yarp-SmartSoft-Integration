 /*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include <yarp/smartsoft/PatternClientBase.h>

using namespace yarp::smartsoft;


bool PatternClientBase::disconnectAllSrv()
{
    if (!m_port)
        return false;
    bool ok = true;
    for (auto srvName : m_serverNames) {
        if (!yarp::os::Network::disconnect(m_port->getName(), srvName))
        {
            yError()<<"SendClient: unable to disconnect from the SendServer:"<<srvName;
            ok = false;
        }
    }
    return ok;
}

bool PatternClientBase::connectAllSrv()
{
    if (!m_port)
        return false;
    bool ok = true;
    for (auto srvName : m_serverNames) {
        if (!yarp::os::Network::connect(m_port->getName(), srvName))
        {
            yError()<<"SendClient: unable to connect to the SendServer:"<<srvName;
            ok = false;
        }
    }
    return ok;
}

Smart::StatusCode PatternClientBase::add(const std::string &portName) throw()
{
    if (!m_port)
        return Smart::SMART_ERROR;

    bool ok = true;
    if (yarp::os::Network::exists(portName))
    {
        return Smart::SMART_PORTALREADYUSED;
    }
    if (m_port->isOpen())
    {
        m_port->interrupt();
        m_port->close();
    }

    if (m_port->open(portName))
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

Smart::StatusCode PatternClientBase::remove() throw()
{
    if (!m_port)
        return Smart::SMART_ERROR;
    // FIXME: how do we maintain the connections without the port???
    m_port->interrupt();
    m_port->close();
    return Smart::SMART_OK;
}

Smart::StatusCode PatternClientBase::connect(const std::string& server, const std::string& service) throw()
{
    if (!m_port)
        return Smart::SMART_ERROR;
    //FIXME: use it
    YARP_UNUSED(service);
    if (!yarp::os::Network::connect(m_port->getName(), server))
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

Smart::StatusCode PatternClientBase::disconnect() throw()
{
    bool ok = disconnectAllSrv();
    m_serverNames.clear();
    return ok ? Smart::SMART_OK : Smart::SMART_ERROR;
}
