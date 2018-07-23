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
#include <yarp/os/RpcClient.h>
#include <yarp/smartsoft/PatternClientBase.h>

#include <aceSmartSoft.hh>

namespace yarp {
namespace smartsoft {

class QueryPatternClient : public PatternClientBase
{
public:
    QueryPatternClient() = delete;

    QueryPatternClient(const QueryPatternClient& rhs) = delete;

    /**
     * @brief QueryPatternClient
     * @param portName
     * @param srvName
     * @param service
     */
    QueryPatternClient(const std::string& portName, const std::string& srvName ="",
                       const std::string& service = "") throw(SmartACE::SmartError)
    {
        YARP_UNUSED(service);//FIXME: use it!

        if (!yarp::os::Network::checkNetwork() || portName.empty() || !m_rpcClient.open(portName))
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,
                                       "CommPattern (queryClient): ERROR: unable to open YARP port"));
        }

        m_port = &(m_rpcClient.asPort());
        // FIXME: to be tested what actually does....
        m_rpcClient.setRpcMode(true);

        if (!srvName.empty())
        {
            if (!yarp::os::Network::connect(m_rpcClient.getName(), srvName))
            {
                throw(SmartACE::SmartError(Smart::SMART_ERROR,
                                           "CommPattern (sendClient): ERROR: unable to connect to "+srvName));
            }
            m_serverNames.emplace_back(srvName);
        }
    }

    virtual ~QueryPatternClient() throw()
    {
        this->disconnect();
        this->remove();
        if (m_port)
        {
            delete m_port;
        }
    }

private:
    yarp::os::RpcClient m_rpcClient;
    std::vector<std::string> m_serverNames;// FIXME initialization missing



};

} // namespace smartsoft
} // namespace yarp

#endif // YARP_SMARTSOFT_QUERYPATTERNCLIENT_H
