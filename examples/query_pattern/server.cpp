/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include <yarp/smartsoft/QueryPatternServer.h>

using namespace yarp::os;
using namespace yarp::smartsoft;


int main()
{
    Network yarp;
    QueryPatternServer<Bottle,Bottle> qps("/query_pattern/server");
    return 0;
}
