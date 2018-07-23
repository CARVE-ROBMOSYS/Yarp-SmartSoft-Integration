/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SMARTSOFT_IMPL_PATTERNCLIENTBASE_H
#define YARP_SMARTSOFT_IMPL_PATTERNCLIENTBASE_H
#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>

#include <memory>
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
     * @brief blocking
     * @param flag
     * @return
     */
    virtual Smart::StatusCode blocking(const bool flag) throw() = 0;

    /**
     * @brief add
     * @param portName
     * @return
     */
    virtual Smart::StatusCode add(const std::string& portName) throw();

    /**
     * @brief remove
     * @return
     */
    virtual Smart::StatusCode remove() throw();

    /**
     * @brief connect
     * @param server
     * @param service
     * @return
     */
    virtual Smart::StatusCode connect(const std::string& server, const std::string& service="") throw();

    /**
     * @brief disconnect
     * @return
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

#endif // YARP_SMARTSOFT_IMPL_PATTERNCLIENTBASE_H
