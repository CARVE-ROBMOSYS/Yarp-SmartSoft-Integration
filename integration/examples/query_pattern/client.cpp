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


void checkAnswer(QueryPatternClient<Bottle,Bottle> &client, const Smart::StatusCode statusQuery, const uint32_t ID, Bottle &answer, bool wait=false)
{

    if (statusQuery == Smart::SMART_DISCONNECTED)
    {
        yError()<<"The client is not connected to nobody...";
    }
    else if(statusQuery == Smart::SMART_ERROR_COMMUNICATION)
    {
        yError()<<"Something is not working in the communication...";
    }
    else
    {
        Smart::StatusCode statusRecv;
        answer.clear();
        if(!wait)
            statusRecv= client.queryReceive(ID, answer);
        else
            statusRecv = client.queryReceiveWait(ID, answer, 5s);

        if ( statusRecv == Smart::SMART_NODATA)
            yWarning() << "The result with ID: " << ID << " Not yet data\n";
        else if (statusRecv == Smart::SMART_OK)
            yInfo() << "The result with \t ID: " << ID << " is: " << answer.toString() << "\n";
    }
}

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
    yInfo() << "Query is   \t" << req.toString();
    Smart::StatusCode status =  qpc.query(req, ans);
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
        yInfo()<<"The result is \t" << ans.toString() << "\n";
    }


    req.clear();
    // testing queryRequest
    req.addString("sum");
    req.addInt32(4);
    req.addInt32(5);

    uint32_t ticket{0};
    status = qpc.queryRequest(req, ticket);
    yInfo() << "Query request  \t ID: " << ticket << " R: " << req.toString();

    yarp::os::Time::delay(0.5);
    checkAnswer(qpc, status, ticket, ans);
    yarp::os::Time::delay(0.5);
    checkAnswer(qpc, status, ticket, ans);
    yarp::os::Time::delay(2);
    checkAnswer(qpc, status, ticket, ans);


    yarp::os::Time::delay(1);

    // testing consequent requests..
    req.clear();
    req.addString("sum");
    req.addInt32(6);
    req.addInt32(6);

    Bottle req2;
    req2.addString("sum");
    req2.addInt32(7);
    req2.addInt32(7);

    Bottle req3;
    req3.addString("sum");
    req3.addInt32(100);
    req3.addInt32(100);

    uint32_t ticket1{0}, ticket2{0}, ticket3{0};
    Smart::StatusCode status1, status2, status3;

    status1 = qpc.queryRequest(req, ticket1);
    yInfo() << "Query request  \t ID: " << ticket1 << " R: " << req.toString();

    yInfo() << "Query is   \t" << req2.toString();
    status2 =  qpc.query(req2, ans);
    yInfo()<<"The result is \t" << ans.toString() << "\n";

    status3 = qpc.queryRequest(req3, ticket3);
    yInfo() << "Query request  \t ID: " << ticket3 << " R: " << req3.toString();

    yarp::os::Time::delay(0.3);
    checkAnswer(qpc, status3, ticket3, ans);
    checkAnswer(qpc, status1, ticket1, ans);

    // testing queryRequest
    req.clear();
    req.addString("sum");
    req.addInt32(8);
    req.addInt32(8);

    status = qpc.queryRequest(req, ticket);
    yInfo() << "Query request ID: " << ticket << " R: " << req.toString() << "\n";

    checkAnswer(qpc, status1, ticket1, ans, true);
    checkAnswer(qpc, status3, ticket3, ans, true);
    checkAnswer(qpc, status,  ticket,  ans, true);

    yInfo() << "Query receive with non-existing ID";
    ans.clear();
    status = qpc.queryReceiveWait(100, ans, 1s);
    if (status != Smart::SMART_OK)
        yInfo()<<"It is not arrived as expected";

    return 0;
}
