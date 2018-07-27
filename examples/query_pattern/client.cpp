/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include <yarp/smartsoft/QueryPatternClient.h>

using namespace yarp::os;
using namespace yarp::smartsoft;
using namespace std::chrono_literals;

int main()
{
    Network yarp;
    QueryPatternClient<Bottle,Bottle> qpc("/query_pattern/client");

    int trials = 1000;
    while (Smart::SMART_OK != qpc.connect("/query_pattern/server"))
    {
        if (0 == trials)
        {
            yError()<<"It was impossible to connect to the SendServer, closing...";
            return 1;
        }
        trials--;
        yarp::os::Time::delay(1.0);
    }

    Bottle req, ans;


    // testing query
    req.addString("sum");
    req.addInt32(2);
    req.addInt32(2);
    Smart::StatusCode status =  qpc.query(req,ans);
    if (status == Smart::SMART_DISCONNECTED)
    {
        yError()<<"The client is not connected to nobody...";
    }
    else if(status == Smart::SMART_ERROR_COMMUNICATION)
    {
        yError()<<"Something is not working in the communication...";
    }
    else
    {
        yInfo()<<"The result of operation is"<<ans.toString();
    }


    req.clear();
    // testing queryRequest
    req.addString("sum");
    req.addInt32(4);
    req.addInt32(5);

    uint32_t ticket{0};
    status = qpc.queryRequest(req, ticket);

    yarp::os::Time::delay(0.3);
    if (status == Smart::SMART_DISCONNECTED)
    {
        yError()<<"The client is not connected to nobody...";
    }
    else if(status == Smart::SMART_ERROR_COMMUNICATION)
    {
        yError()<<"Something is not working in the communication...";
    }
    else
    {
        ans.clear();
        status = qpc.queryReceive(ticket, ans);
        if ( status == Smart::SMART_NODATA)
            yError("No yet data");
        else if (status == Smart::SMART_OK)
            yInfo()<<"The result of operation is"<<ans.toString();
    }
    req.clear();
    // testing consequent requests..

    req.addString("sum");
    req.addInt32(6);
    req.addInt32(6);

    Bottle req2;
    req2.addString("sum");
    req2.addInt32(7);
    req2.addInt32(7);

    uint32_t ticket1{0}, ticket2{0};
    Smart::StatusCode status1 = qpc.queryRequest(req, ticket1);
    Smart::StatusCode status2 = qpc.queryRequest(req2, ticket2);

    yarp::os::Time::delay(0.3);
    if (status2 == Smart::SMART_DISCONNECTED)
    {
        yError()<<"The client is not connected to nobody...";
    }
    else if(status2 == Smart::SMART_ERROR_COMMUNICATION)
    {
        yError()<<"Something is not working in the communication...";
    }
    else
    {
        ans.clear();
        status = qpc.queryReceive(ticket2, ans);
        if ( status == Smart::SMART_NODATA)
            yError("No yet data");
        else if (status == Smart::SMART_OK)
            yInfo()<<"The result of operation is"<<ans.toString();
    }

    if (status1 == Smart::SMART_DISCONNECTED)
    {
        yError()<<"The client is not connected to nobody...";
    }
    else if(status1 == Smart::SMART_ERROR_COMMUNICATION)
    {
        yError()<<"Something is not working in the communication...";
    }
    else
    {
        ans.clear();
        status = qpc.queryReceive(ticket1, ans);
        if ( status == Smart::SMART_NODATA)
            yError("No yet data");
        else if (status == Smart::SMART_OK)
            yInfo()<<"The result of operation is"<<ans.toString();
    }

    req.clear();
    // testing queryRequest
    req.addString("sum");
    req.addInt32(8);
    req.addInt32(8);

    status = qpc.queryRequest(req, ticket);
    if (status == Smart::SMART_DISCONNECTED)
    {
        yError()<<"The client is not connected to nobody...";
    }
    else if(status == Smart::SMART_ERROR_COMMUNICATION)
    {
        yError()<<"Something is not working in the communication...";
    }
    else
    {
        ans.clear();
        status = qpc.queryReceiveWait(ticket, ans, 10s);
        if ( status == Smart::SMART_NODATA)
            yError("No yet data");
        else if (status == Smart::SMART_OK)
            yInfo()<<"The result of operation is"<<ans.toString();
    }

    yInfo()<<"Waiting for 1 sec something will never arrive";
    status = qpc.queryReceiveWait(100, ans, 1s);
    if (status != Smart::SMART_OK)
        yInfo()<<"It is not arrived as expected";


    return 0;
}
