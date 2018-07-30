/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include <yarp/os/LogStream.h>
#include <yarp/smartsoft/PushPatternServer.h>

using namespace yarp::os;
using namespace yarp::smartsoft;


int main()
{
    Network yarp;
    PushPatternServer<Bottle> ppc("/push_pattern/server");
    int i = 0;
    while (true)
    {
        i++;
        Bottle bt;
        yInfo()<<"The PushServer is running...";
        bt.addInt32(i);
        ppc.put(bt);
        yarp::os::Time::delay(0.5);
    }
    return 0;
}
