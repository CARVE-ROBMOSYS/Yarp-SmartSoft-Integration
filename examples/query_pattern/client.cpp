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

int main()
{
    Network yarp;
    QueryPatternClient<Bottle,Bottle> qpc("/query_pattern/client");

    int trials = 10;
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
        yInfo()<<"The resul of operation is"<<ans.get(0).asInt32();
    }

    yarp::os::Time::delay(1.0);

    return 0;
}
