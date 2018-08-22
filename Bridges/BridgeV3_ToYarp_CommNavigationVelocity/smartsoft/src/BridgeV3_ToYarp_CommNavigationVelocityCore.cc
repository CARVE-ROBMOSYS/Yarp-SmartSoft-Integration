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
#include "BridgeV3_ToYarp_CommNavigationVelocityCore.hh"

// constructor
BridgeV3_ToYarp_CommNavigationVelocityCore::BridgeV3_ToYarp_CommNavigationVelocityCore()
{
	std::cout << "constructor BridgeV3_ToYarp_CommNavigationVelocityCore\n";
}


void BridgeV3_ToYarp_CommNavigationVelocityCore::onStartup()
{
	std::cout << "<<<<< BridgeV3_ToYarp_CommNavigationVelocityCore::init() >>>>> ";
	// Check yarp network
	if(!yarp.checkNetwork(2))
	{
		std::cerr << "Cannot find YARP network, is the yarpserver running and reachable?";
		throw std::runtime_error("Cannot find YARP network, is the yarpserver running and reachable?");
	}

	bool ret = false;
	std::string localPortName;
	std::string remotePortName;

	ret = commandPort.open(localPortName);

	if(!ret)
	{
		std::string errorStr = " Cannot open port \"" + localPortName + "\"";
		throw std::invalid_argument("portname");
	}
}
