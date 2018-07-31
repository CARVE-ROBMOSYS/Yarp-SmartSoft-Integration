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
#include <yarp/os/PortablePair.h>
#include <yarp/os/RpcServer.h>
#include <yarp/smartsoft/SmartVocabs.h>

#include <aceSmartSoft.hh>

#include <map>

namespace yarp {
namespace smartsoft {

template<class R, class A>
class QueryPatternServer;

/**
 * @brief The QueryPatternServerHandler class
 */
template <class R, class A>
class QueryPatternServerHandler
{
public:
    /**
     * @brief QueryPatternServerHandler constructor
     */

    QueryPatternServerHandler()
    {}

    /**
     * @brief ~QueryPatternServerHandler
     */
    virtual ~QueryPatternServerHandler()
    {}

    /**
     * @brief
     * Callback to be implemented, it is called every time a new request reach the server.
     * @param server, pointer to the QueryPatternServer
     * @param idReq, identifier of the request.
     * @param datum, request to be handled.
     */
    virtual void handleQuery(QueryPatternServer<R,A>* server, const int32_t idReq, const R& datum) throw() = 0;
};

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
     * @param portName, name of the port associated to the server.
     * @param serverHandler, pointer to the query handler.
     * @param service, name of the service.
     */
    QueryPatternServer(const std::string portName, QueryPatternServerHandler<R,A>* serverHandler,
                       const std::string& service = "") throw(SmartACE::SmartError) : m_query_handler_ptr{serverHandler}
    {
        // FIXME: USE IT!
        YARP_UNUSED(service);
        if (!m_query_handler_ptr)
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (queryServer): ERROR: query handler invalid"));
        }
        if (!yarp::os::Network::checkNetwork() || portName.empty() || !m_rpc_server.open(portName))
        {
            throw(SmartACE::SmartError(Smart::SMART_ERROR,"CommPattern (queryServer): ERROR: unable to open YARP port"));
        }
        // The server can only receive.
        m_rpc_server.setReader(*this);
    }

    virtual ~QueryPatternServer() throw()
    {
        m_rpc_server.interrupt();
        m_rpc_server.close();
    }

    /**
     * @brief
     * Answer to a request identified by <i> id </i>
     * @param id number of the request
     * @param answer answer that has to be sent
     * @return status code:
     *    - SMART_OK           : everything is ok, the answer has been sent.
     *    - SMART_WRONGID      : no pending query with this identifier.
     *    - SMART_DISCONNECTED : the server is not connected to any client.
     *    - SMART_ERROR_COMMUNICATION;        : something went wrong, answer not sent.
     */
    Smart::StatusCode answer(const int32_t& id, const A& answer) throw()
    {
        if (id < 0)
        {
            yError()<<"QueryServer: invalid id, it must be positive";
            return Smart::SMART_WRONGID;
        }
        if (m_rpc_server.getInputCount() == 0)
        {
            yError()<<"QueryServer: no ingoing connections..";
            return Smart::SMART_DISCONNECTED;
        }
        return (answer.write(*m_connection->getWriter())) ? Smart::SMART_OK : Smart::SMART_ERROR_COMMUNICATION;
    }

protected:
    virtual bool read(yarp::os::ConnectionReader& connection)
    {
        yarp::os::PortablePair<yarp::os::Bottle, R> message;
        if (!message.read(connection))
        {
            return false;
        }
        if (message.head.get(0).asInt32() == vocab_query_id)
        {
            uint32_t _id = message.head.get(1).asInt32();
            m_connection = &connection;
            m_query_handler_ptr->handleQuery(this, _id, message.body);
            return true;
        }
        return false;
    }
private:
    yarp::os::RpcServer m_rpc_server;
    QueryPatternServerHandler<R,A>* m_query_handler_ptr;
    yarp::os::ConnectionReader* m_connection {nullptr};

};

} // namespace smartsoft
} // namespace yarp
#endif // YARP_SMARTSOFT_QUERYPATTERNSERVER_H
