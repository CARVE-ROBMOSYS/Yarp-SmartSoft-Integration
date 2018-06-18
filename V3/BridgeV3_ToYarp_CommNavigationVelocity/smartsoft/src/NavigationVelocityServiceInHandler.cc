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
#include "NavigationVelocityServiceInHandler.hh"
#include "BridgeV3_ToYarp_CommNavigationVelocity.hh"

#include <iostream>

NavigationVelocityServiceInHandler::NavigationVelocityServiceInHandler(Smart::InputSubject<CommBasicObjects::CommNavigationVelocity> *subject, const int &prescaleFactor)
:	NavigationVelocityServiceInHandlerCore(subject, prescaleFactor)
{
	std::cout << "constructor NavigationVelocityServiceInHandler\n";
	std::cout << "gattiiiiiiiii\n";
	std::cout << "gattiiiiiiiii\n";
	std::cout << "gattiiiiiiiii\n";
	std::cout << "gattiiiiiiiii\n";
	std::cout << "gattiiiiiiiii ovunqueee!!!\n";
}
NavigationVelocityServiceInHandler::~NavigationVelocityServiceInHandler() 
{
	std::cout << "destructor NavigationVelocityServiceInHandler\n";
}

void NavigationVelocityServiceInHandler::on_NavigationVelocityServiceIn(const CommBasicObjects::CommNavigationVelocity &input)
{
	// implement business logic here
	// (do not use blocking calls here, otherwise this might block the InputPort NavigationVelocityServiceIn)
	yarp::os::Bottle & velCmd = COMP->commandPort.prepare();
	std::cout << "Got a new message";
	velCmd.clear();
	velCmd.addDouble(input.getVX());
	velCmd.addDouble(input.getVY());
	velCmd.addDouble(input.getOmega());
	COMP->commandPort.write();
	std::cout << "Sent cmd via yarp -> " << velCmd.toString();
}

