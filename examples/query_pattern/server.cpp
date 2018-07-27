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
            std::string operation = datum.get(0).asString();
            if (operation == "sum")
            {
                answer.addInt32(datum.get(1).asInt32()+datum.get(2).asInt32());
            }
            else if (operation == "subtraction")
            {
                answer.addInt32(datum.get(1).asInt32()-datum.get(2).asInt32());
            }
            else if (operation == "subtraction")
            {
                answer.addInt32(datum.get(1).asInt32()*datum.get(2).asInt32());
            }
            else
            {
                yError()<<"MyHandler"<<operation<<"not supported";
                return;
            }

            // do stuff...
            yInfo()<<"MyHandler: answering with"<<answer.toString();
            int32_t status_code = server->answer(idReq, answer);
            if (status_code == Smart::SMART_OK)
            {
                yInfo()<<"MyHandler: answer"<<answer.toString()<<"successfully sent";
            }
            if (status_code == Smart::SMART_ERROR)
            {
                yError()<<"MyHandler: failed to answer";
            }
        }
    }
};
int main()
{
    Network yarp;
    MyQueryHandler hdlr;
    QueryPatternServer<Bottle,Bottle> qps("/query_pattern/server", &hdlr);
    while (true)
    {
        yInfo()<<"The QueryServer is running...";
        yarp::os::Time::delay(0.5);
    }
    return 0;
}
