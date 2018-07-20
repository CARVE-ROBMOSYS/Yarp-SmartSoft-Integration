/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include <yarp/smartsoft/SendPatternClient.h>

using namespace yarp::os;
using namespace yarp::smartsoft;

int main()
{
    Network yarp;
    SendPatternClient<Bottle> spc("/send_pattern/client");
    int trials = 10;
    while (Smart::SMART_OK != spc.connect("/send_pattern/server"))
    {
        if (0 == trials)
        {
            yError()<<"It was impossible to connect to the SendServer, closing...";
            return 1;
        }
        trials--;
        yarp::os::Time::delay(1.0);
    }

    for (int i=0; i<10; i++)
    {
        Bottle bt;
        bt.addString("magic number");
        bt.addInt32(i);
        Smart::StatusCode status = spc.send(bt);
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
            yInfo()<<"The client correctly sent"<<i<<"...";
        }
        yarp::os::Time::delay(0.001);
    }

    yarp::os::Time::delay(1.0);

    return 0;
}
