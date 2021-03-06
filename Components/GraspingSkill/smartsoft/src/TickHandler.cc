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
#include "TickHandler.hh"
#include "GraspingSkill.hh"

#include <BTMonitorMsg.h>
#include <yarp/os/LogStream.h>

using namespace std;
using namespace yarp::os;

TickHandler::TickHandler(Smart::IQueryServerPattern<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult, SmartACE::QueryId>* server)
:	TickHandlerCore(server)
{
	bool ret = false;
	COMP->RPChome.open("/SmartSoft/homing");
	COMP->RPCgrasp.open("/SmartSoft/grasping");

	yarp::os::Network::connect(COMP->RPChome.getName(),  "/action-gateway/cmd:io");
	yarp::os::Network::connect(COMP->RPCgrasp.getName(), "/graspProcessor/cmd:rpc");

	ret = COMP->blackBoard_Client.open("/GraspingSkill/blackboard:o");
	ret &= yarp::os::Network::connect("/GraspingSkill/blackboard:o", "/blackboard/rpc:i");
	if(!ret)
	{
		yError() << "Cannot connect to YARP blackboard";	yarp::os::Port  blackBoard_Client;

	}
	toMonitor_port.open("/graspingSkill/monitor:o");
}

TickHandler::~TickHandler()
{
	
}

// TDB:  change and use the thread
void TickHandler::handleQuery(const SmartACE::QueryId &id, const CommYARP_BT::CommTickCommand& request) 
{
	// init helper variables
	CommYARP_BT::CommTickResult answer;
	CommYARP_BT::TickResult result = CommYARP_BT::TickResult::Failure;

	// debug print
	std::cout << "Received request " << request.getCommand() << "  --  " << request.getParameter() << std::endl;

	// handle input parameters
	CommYARP_BT::TickCommand::ENUM_TickCommand cmd = request.getCommand();

	// Parse param string into vector
	std::string params = request.getParameter();
	vector<string> paramsVect;
	stringstream ss(params);
	string temp;
	while (ss >> temp)
		paramsVect.push_back(temp);

	string skillName;

	switch(cmd)
	{
		case CommYARP_BT::TickCommand::Tick:
		{
			if(paramsVect[0] == "KeepArmsForGrasp")
			{
				skillName = paramsVect[0];
				{
					// send signal to the monitors
			        BTMonitorMsg msg;
			        msg.skill     = skillName;
			        msg.event     = "e_req";
			        toMonitor_port.write(msg);
				}


				yarp::os::Bottle cmd;
				cmd.addString("home");
				cmd.addString("arms");
				bool ret = COMP->RPChome.write(cmd);
				yInfo() << "homeArms ret " << ret << " cmd " << cmd.toString();
				result = CommYARP_BT::TickResult::Success;
			}

			if(paramsVect[0] == "homeHead")
			{
				yarp::os::Bottle cmd;
				cmd.addString("home head");
				bool ret = COMP->RPChome.write(cmd);
				yInfo() << "homeHead ret " << ret << " cmd " << cmd.toString();
				result = CommYARP_BT::TickResult::Success;
			}

			if(paramsVect[0] == "grasp")
			{
				skillName = string("Grasp") + paramsVect[1];
				{
					// send signal to the monitors
			        BTMonitorMsg msg;
			        msg.skill     = skillName;
			        msg.event     = "e_req";
			        toMonitor_port.write(msg);
				}

				yarp::os::Bottle cmd, reply;
				cmd.addString("grasp");
				cmd.addString(paramsVect[1]);
				cmd.addString("right");
				bool ret = COMP->RPCgrasp.write(cmd, reply);
				yInfo() << "grasp ret " << ret << " cmd " << cmd.toString() << " reply " << reply.toString();

				if(reply.toString() == "[ack]")
				{
						result = CommYARP_BT::TickResult::Success;
						Bottle toBoard, reply;
						toBoard.addString("set");
						toBoard.addString("BottleGrasped");
						toBoard.addString("True");
						bool ret = COMP->blackBoard_Client.write(toBoard, reply);
						yInfo() << "Bottle grasped!!! ret " << ret;
				}
				else
				{
					result = CommYARP_BT::TickResult::Running;
					yDebug() << "Running";
				}
			}
		} break;

		case CommYARP_BT::TickCommand::Halt:
		{
			// Dummy halt
			result = CommYARP_BT::TickResult::Halted;
		} break;
	}

	if(result == CommYARP_BT::TickResult::Success)
	{
		// send signal to the monitors
        BTMonitorMsg msg;
        msg.skill     = skillName;
        msg.event     = "e_from_env";
        toMonitor_port.write(msg);
	}
	// implement your query handling logic here and fill in the answer object
	answer.setResult(result);
	this->server->answer(id, answer);
}
