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
#include "BehaviourTreeTickQueryServiceAnswHandler.hh"
#include "Test_QueryServer.hh"

BehaviourTreeTickQueryServiceAnswHandler::BehaviourTreeTickQueryServiceAnswHandler(Smart::IQueryServerPattern<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult, SmartACE::QueryId>* server)
:	BehaviourTreeTickQueryServiceAnswHandlerCore(server)
{
	
}

BehaviourTreeTickQueryServiceAnswHandler::~BehaviourTreeTickQueryServiceAnswHandler()
{
	
}


void BehaviourTreeTickQueryServiceAnswHandler::handleQuery(const SmartACE::QueryId &id, const CommYARP_BT::CommTickCommand& request) 
{
	CommYARP_BT::CommTickResult answer;
	
	// implement your query handling logic here and fill in the answer object
	CommYARP_BT::TickResult result = CommYARP_BT::TickResult::Success;
	std::cout << request << "  " << result << std::endl;

	answer.setResult(result);
	this->server->answer(id, answer);
}
