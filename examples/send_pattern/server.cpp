/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include <yarp/smartsoft/SendPatternServer.h>

using namespace yarp::os;
using namespace yarp::smartsoft;


class MyBottleHandler : public SendPatternServerHandler<Bottle>
{
public:
    MyBottleHandler(): m_srv(nullptr){}

    MyBottleHandler(SendPatternServer<Bottle> *server) : m_srv(server)
    {}

    virtual ~MyBottleHandler()
    {}

    virtual void handleSend(const Bottle& datum) throw() override
    {
        yInfo()<<"MyBottleHandler: hey, I'm receiving a bottle of size:"<<datum.size();
        yInfo()<<"MyBottleHandler: it contains"<<datum.toString();
    }
private:
SendPatternServer<Bottle>* m_srv;

};

int main()
{
    Network yarp;
    MyBottleHandler btHandler;
    SendPatternServer<Bottle> sps("/send_pattern/server", &btHandler);
    while (true)
    {
        yInfo()<<"The SendServer is running...";
        yarp::os::Time::delay(0.5);
    }

    return 0;
}
