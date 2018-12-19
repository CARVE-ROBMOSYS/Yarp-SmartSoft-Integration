//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#include <string>
#include <iostream>

#include "BT_tick_Handler.hh"
#include "YarpNavigationClient.hh"

#include <yarp/os/Vocab.h>
#include <yarp/os/LogStream.h>

using namespace std;
using namespace yarp::os;

BT_tick_Handler::BT_tick_Handler(Smart::IQueryServerPattern<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult, SmartACE::QueryId>* server)
:	BT_tick_HandlerCore(server)
{
	bool ret = false;
	std::cout << "BT_tick_Handler::BT_tick_Handler" << std::endl;
	ret = blackBoard_Client.open("/yarpNavigationClient/blackboard:o");
	ret &= yarp::os::Network::connect(blackBoard_Client.getName(), "/blackboard/rpc:i");
	if(!ret)
	{
		yError() << "Cannot connect to YARP blackboard";
	}
}

BT_tick_Handler::~BT_tick_Handler()
{
	
}


void BT_tick_Handler::handleQuery(const SmartACE::QueryId &id, const CommYARP_BT::CommTickCommand& request) 
{
	// init values
	CommYARP_BT::CommTickResult answer;
	CommYARP_BT::TickResult result = CommYARP_BT::TickResult::Failure;
	yarp::dev::NavigationStatusEnum status = yarp::dev::navigation_status_error;

	// debug prints
	std::cout << "\n*********************************************" << std::endl;
	std::cout << "Received request " << request.getCommand() << "  --  " << request.getParameter() << std::endl;
	std::cout << "has goal " << has_goal << std::endl;


	// implement your query handling logic here and fill in the answer object

	CommYARP_BT::TickCommand::ENUM_TickCommand cmd = request.getCommand();

	// Parse param string into vector
	std::string params = request.getParameter();
	vector<string> paramsVect;
	stringstream ss(params);
	string temp;
	while (ss >> temp)
		paramsVect.push_back(temp);

	for(int i=0; i< paramsVect.size(); i++)
		yInfo() << "param [" << i << "] is " << paramsVect[i];

	// Get absolute position of 'location' from blackboard
	Bottle toBoard, reply;
	toBoard.addString("get");
	toBoard.addString(paramsVect[1]);
	blackBoard_Client.write(toBoard, reply);

	yDebug() << "Got reply from blackboard " << reply.toString();

	// get actual data from string reply
	yarp::dev::Map2DLocation desiredLoc;
	stringstream ss2(reply.toString().c_str()+1);
	ss2 >> desiredLoc.map_id;
	ss2 >> desiredLoc.x;
	ss2 >> desiredLoc.y;
	ss2 >> desiredLoc.theta;

	yInfo() << "desired Loc is " << desiredLoc.toString();

	// handle command
	switch(cmd)
	{
		case CommYARP_BT::TickCommand::Tick:
		{
			// Get subcommand: goTo or check
			if(paramsVect[0] == "goTo")
				result = handle_tick_goTo(desiredLoc);

			if(paramsVect[0] == "check")
				result = handle_tick_check(desiredLoc);
		} break;

		case CommYARP_BT::TickCommand::Halt:
		{
			COMP->iNav->stopNavigation();
			has_goal = false;
			result = CommYARP_BT::TickResult::Success;
		} break;
	}

	answer.setResult(result);

	// Debug print
	yDebug() << "ID " <<  id << " req " << request.getParameter() << "; result " << result.to_string();

	this->server->answer(id, answer);
}

CommYARP_BT::TickResult  BT_tick_Handler::handle_tick_goTo(yarp::dev::Map2DLocation location)
{
	CommYARP_BT::TickResult result = CommYARP_BT::TickResult::Failure;
	if(!handle_tick_check(location))
	{
		yInfo() << "Location reached";
		result = CommYARP_BT::TickResult::Success;
		return result;
	}

	yarp::dev::NavigationStatusEnum status = yarp::dev::navigation_status_error;

	if(has_goal)
	{
		COMP->iNav->getNavigationStatus(status);
		std::cout << " navigation status " << yarp::os::Vocab::decode(status) << std::endl;

		switch(status)
		{
			case yarp::dev::navigation_status_goal_reached:
			case yarp::dev::navigation_status_idle:
				result = CommYARP_BT::TickResult::Success;
				has_goal = false;
				break;

			case yarp::dev::navigation_status_error:
			case yarp::dev::navigation_status_failing:
				result = CommYARP_BT::TickResult::Failure;
				has_goal = false;
				break;

			default:
				result = CommYARP_BT::TickResult::Running;
		}
	}
	else
	{
		std::cout << "Calling gotoTargetByAbsoluteLocation..." << std::endl ;
		if( COMP->iNav->gotoTargetByAbsoluteLocation(location) )   // this may require some time (???)
		{
			result = CommYARP_BT::TickResult::Running;
			has_goal = true;
		}
		std:: cout << "Returning" << std::endl;
	}
	return result;
}

CommYARP_BT::TickResult BT_tick_Handler::handle_tick_check(yarp::dev::Map2DLocation desiredLoc)
{
	CommYARP_BT::TickResult result = CommYARP_BT::TickResult::Failure;

	// get actual data from string reply
	yarp::dev::Map2DLocation robotLoc;

	// get current robot position
	bool ret = COMP->iNav->getCurrentPosition(robotLoc);

	yInfo() << "Get [" << ret << "] Current robot location is " << robotLoc.toString();


	std::cout << std::fabs(desiredLoc.x - robotLoc.x) << std::endl;
	std::cout << std::fabs(desiredLoc.y - robotLoc.y) << std::endl;
	std::cout << std::fabs(desiredLoc.theta - robotLoc.theta) << std::endl;

	// Position matches if robot is inside a 0.1 circle.
	if( std::fabs(desiredLoc.x 		- robotLoc.x)     <= 0.1 &&
		std::fabs(desiredLoc.y 		- robotLoc.y)     <= 0.1 ) // &&
		// std::fabs(desiredLoc.theta 	- robotLoc.theta) <= 0.1 )
	{
		result = CommYARP_BT::TickResult::Success;
	}
	else
	{
		result = CommYARP_BT::TickResult::Failure;
	}
	return result;
}

