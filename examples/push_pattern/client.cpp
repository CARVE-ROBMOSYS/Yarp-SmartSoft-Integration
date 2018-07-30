/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include <yarp/smartsoft/PushPatternClient.h>


using namespace yarp::os;
using namespace yarp::smartsoft;
using namespace std::chrono_literals;
int main()
{
    Network yarp;
    PushPatternClient<Bottle> ppc("/push_pattern/client");
    int trials = 100;
    ppc.connect("/push_pattern/server");
    while (Smart::SMART_OK != ppc.subscribe())
    {
        if (0 == trials)
        {
            yError()<<"It was impossible to connect to the SendServer, closing...";
            return 1;
        }
        trials--;
        yarp::os::Time::delay(1.0);
    }


    yInfo()<<"************ blocking updates ************";
    for (int i=0; i<5; i++)
    {
        Bottle btIn;
        if(ppc.getUpdateWait(btIn, 10s) == Smart::SMART_OK)
        {
            yInfo()<<"Received:"<<btIn.get(0).asInt32();
        }
    }

    yInfo()<<"************ non blocking updates ************";
    for (int i=0; i<5; i++)
    {
        Bottle btIn;
        if(ppc.getUpdate(btIn) == Smart::SMART_OK)
        {
            yInfo()<<"Received:"<<btIn.get(0).asInt32();
        }
        yarp::os::Time::delay(0.3);
    }
    double period=0.0;
    bool active=false;
    ppc.getServerInfo(period, active);
    yInfo()<<"STATS: period:"<<period<<"status"<<active;

    return 0;
}
