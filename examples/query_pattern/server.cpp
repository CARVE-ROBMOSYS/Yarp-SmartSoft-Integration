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

class MyQueryHandler : public QueryPatternServerHandler<Bottle,Bottle>
{
    void handleQuery(QueryPatternServer<Bottle,Bottle>* server, const int32_t idReq, const Bottle& datum) throw() override
    {
        if (server)
        {
            Bottle answer;
            // do stuff...
            int32_t status_code = server->answer(idReq, answer);

        }
    }

};
int main()
{
    Network yarp;
    MyQueryHandler hdlr;
    QueryPatternServer<Bottle,Bottle> qps("/query_pattern/server", &hdlr);
    yarp::os::Time::delay(1.0);
    return 0;
}
