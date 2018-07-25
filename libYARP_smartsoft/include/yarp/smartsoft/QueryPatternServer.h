/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SMARTSOFT_QUERYPATTERNSERVER_H
#define YARP_SMARTSOFT_QUERYPATTERNSERVER_H
#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>

#include <aceSmartSoft.hh>
#include <map>

namespace yarp {
namespace smartsoft {

/**
 * @brief The QueryPatternServer class
 */
template<class R, class A>
class QueryPatternServer : yarp::os::PortReader
{
public:
    QueryPatternServer() = delete;
    /**
     * @brief QueryPatternServer
     * @param portName
     * @param serverHandler
     * @param service
     */
    QueryPatternServer(const std::string portName, const std::string& service = "") throw(SmartACE::SmartError)
    {
        // FIXME: USE IT!
        YARP_UNUSED(service);
        if (!yarp::os::Network::checkNetwork() || portName.empty() || !m_port.open(portName))
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (queryServer): ERROR: unable to open YARP port"));
        }
        // The server can only receive.
        m_port.setReader(*this);
    }

    virtual ~QueryPatternServer() throw()
    {
        m_port.interrupt();
        m_port.close();
    }

    /** Provide answer to be sent back to the requestor.
     *
     *  Member function is thread safe and thread reentrant.
     *
     *  @param id identifies the request to which the answer belongs
     *  @param answer is the reply itself.
     *
     *  @return status code:
     *    - SMART_OK                  : everything is ok and answer sent to requesting client
     *    - SMART_WRONGID             : no pending query with that <I>id</I> known
     *    - SMART_DISCONNECTED        : answer not needed anymore since client
     *                                  got disconnected meanwhile
     *    - SMART_ERROR_COMMUNICATION : communication problems
     *    - SMART_ERROR               : something went wrong
     */
    Smart::StatusCode answer(const uint32_t& id, const A& answer) throw()
    {
        return Smart::SMART_OK;
    }

    Smart::StatusCode check(const uint32_t& id) throw()
    {
        return Smart::SMART_OK;
    }

    Smart::StatusCode discard(const uint32_t& id) throw()
    {
        return Smart::SMART_OK;
    }

protected:
    virtual bool read(yarp::os::ConnectionReader& reader)
    {
        return true;
    }
private:
    // FIXME... is duplicated...(see the client
    struct QueryRequest
    {
        A __answer;
        bool __isReady;
        std::condition_variable __cv;
        QueryRequest(bool isReady=false) : __isReady(isReady)
        {}
    };

    yarp::os::Port m_port;
    std::map<uint32_t, QueryRequest> m_map_req;

};

} // namespace smartsoft
} // namespace yarp
#endif // YARP_SMARTSOFT_QUERYPATTERNSERVER_H
