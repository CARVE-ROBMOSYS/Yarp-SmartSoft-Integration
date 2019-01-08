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
#ifndef _BT_TICK_HANDLER_USER_HH
#define _BT_TICK_HANDLER_USER_HH

#include <string>
#include "BT_tick_HandlerCore.hh"
#include <yarp/os/RpcClient.h>
#include <yarp/dev/Map2DLocation.h>

class BT_tick_Handler : public BT_tick_HandlerCore
{
private:
	bool has_goal{false};
	CommYARP_BT::TickResult handle_tick_goTo(yarp::dev::Map2DLocation  location, std::string locationName);
	CommYARP_BT::TickResult handle_tick_check(yarp::dev::Map2DLocation location);
	yarp::os::RpcClient  blackBoard_Client;

public:
	BT_tick_Handler(Smart::IQueryServerPattern<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult, SmartACE::QueryId>* server);
	virtual ~BT_tick_Handler();
	virtual void handleQuery(const SmartACE::QueryId &id, const CommYARP_BT::CommTickCommand& request);
};
#endif
