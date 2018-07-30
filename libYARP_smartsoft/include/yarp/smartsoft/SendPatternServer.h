/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SMARTSOFT_SENDPATTERNSERVER_H
#define YARP_SMARTSOFT_SENDPATTERNSERVER_H

#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>

#include <aceSmartSoft.hh>

namespace yarp {
namespace smartsoft {
template <class T> class SendPatternServer;

/**
 * @brief The SendPatternServerHandler class
 */
template <class T>
class SendPatternServerHandler : public yarp::os::TypedReaderCallback<T>
{
public:
    SendPatternServerHandler()
    {}
    virtual ~SendPatternServerHandler()
    {}
    virtual void handleSend(const T& datum) throw() = 0;

private:
    using yarp::os::TypedReaderCallback<T>::onRead;
    void onRead(T& datum) override final
    {
        handleSend(datum);
    }
};
/**
 * @brief The SendPatternServer class
 */
template <class T>
class SendPatternServer //: public SmartACE::SendServer<T> FIXME: we need this inheritance??
{
public:
    SendPatternServer() = delete;
    /**
     * @brief SendPatternServer
     * @param portName
     * @param serverHandler
     * @param service
     */
    SendPatternServer(const std::string portName, SendPatternServerHandler<T> *serverHandler, const std::string& service = "") throw(SmartACE::SmartError)
    {
        if (!serverHandler)
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (sendServer): ERROR: invalid sender handler"));
        }
        // FIXME: USE IT!
        YARP_UNUSED(service);
        if (!yarp::os::Network::checkNetwork() || portName.empty() || !m_port.open(portName))
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (sendServer): ERROR: unable to open YARP port"));
        }
        // The server can only receive.
        m_port.setReadOnly();
        m_port.setStrict(true);
        m_port.useCallback(*serverHandler);
    }

    virtual ~SendPatternServer() throw()
    {
        m_port.interrupt();
        m_port.close();
    }
private:
    yarp::os::BufferedPort<T> m_port;

};
} // namespace smartsoft
} // namespace yarp
#endif // YARP_SMARTSOFT_SENDPATTERNSERVER_H
