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

#include "TriggerHandler.hh"

#include "BT_tickDispatcher.hh"

// trigger user methods
void TriggerHandler::handleCommYARP_BT_ConfigParams_configFile(const std::string &filename)
{
	// implement the trigger behavior here. Be aware, if you must use blocking calls here, please set this
	// trigger as active in the model. For an active trigger an active queue will be generated internally 
	// (transparent for the usage here). Thus an active trigger will be called within a separate task scope.
}
