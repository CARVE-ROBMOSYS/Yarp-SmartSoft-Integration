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
}

NavigationVelocityServiceInHandler::~NavigationVelocityServiceInHandler() 
{
	std::cout << "destructor NavigationVelocityServiceInHandler\n";
}

void NavigationVelocityServiceInHandler::on_NavigationVelocityServiceIn(const CommBasicObjects::CommNavigationVelocity &input)
{
	std::cout << "Got a new message: VX " << input.getVX() << " VY: " << input.getVY() << " omega: " << input.get_omega();
	std::cout << "vX " << input.get_vX(1) << " vY: " << input.get_vY(1) << " omega: " << input.get_omega();

	COMP->newData = input;
	COMP->is_newData = true;
	return;
}

