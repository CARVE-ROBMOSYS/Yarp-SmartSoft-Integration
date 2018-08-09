/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SMARTSOFT_PATTERNCLIENTBASE_H
#define YARP_SMARTSOFT_PATTERNCLIENTBASE_H
#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>

#include <aceSmartSoft.hh>

namespace yarp {
namespace smartsoft {

/**
 * @brief The PatternClientBase class, a base class implementing some common
 * functions.
 */
class PatternClientBase
{
public:
    virtual ~PatternClientBase()
    {}

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
    virtual Smart::StatusCode blocking(const bool flag) throw() = 0;

    /** @brief
     * Open a port to associate to this instance. Already
     *  established connections keep valid. If this service
     *  requestor is already exposing a port, it is first
     *  closed and then reopened with the new port name.
     *  add()/remove() and connect()/disconnect() can always
     *  be used to change the status of this instance.
     *
     *  @param portName   name of port used for wiring
     *
     *  @return status code
     *   - SMART_OK                  : everything is OK and the port requested
     *                                 has been opened
     *   - SMART_PORTALREADYUSED     : port name already in use and this
     *   - SMART_ERROR               : something went wrong
     */
    virtual Smart::StatusCode add(const std::string& portName) throw();

    /** @brief
     * Close the port associated with this service requestor.
     *
     *  @return status code
     *   - SMART_OK                  : everything is OK and instance not
     *                                 exposed as port anymore.
     *   - SMART_ERROR               : something went wrong.
     */
    virtual Smart::StatusCode remove() throw();

    /** @brief
     * Connect this service requestor to the denoted service provider. An
     *  already established connection is first disconnected. See disconnect()
     *  for implications on running or pending queries in that case.
     *
     *  @param server   name of the server
     *  @param service  name of the service
     *
     *  @return status code
     *   - SMART_OK                  : everything is OK and connected to the specified service.
     *   - SMART_ERROR               : something went wrong, service requestor is now not connected to any
     *                                 service provider.
     */
    virtual Smart::StatusCode connect(const std::string& server, const std::string& service="") throw();

    /** @brief
     * Disconnect the service requestor from the service provider.
     *
     *  @return status code
     *   - SMART_OK                  : everything is OK and service requestor is disconnected from
     *                                 the service provider.
     *   - SMART_ERROR               : something went wrong. Again at least the service requestor
     *                                 is in the disconnected state.
     */
    virtual Smart::StatusCode disconnect() throw();

private:
    bool disconnectAllSrv();
    bool connectAllSrv();
protected:
    yarp::os::Port* m_port{nullptr};
    std::vector<std::string> m_serverNames;

};

} // namespace smartsoft
} // namespace yarp

#endif // YARP_SMARTSOFT_PATTERNCLIENTBASE_H
