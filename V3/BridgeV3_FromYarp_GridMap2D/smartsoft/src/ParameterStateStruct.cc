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

#include "ParameterStateStruct.hh"

#include "BridgeV3_FromYarp_GridMap2D.hh"

SmartACE::ParamResponseType ParameterStateStruct::handleCOMMIT(const ParameterStateStruct &commitState) {
	// implement any consistency checks here which ensure that the incoming parameter meets components
	// internal constraints. If the current parameter violates any consistency checks, return 
	// SmartACE::ParamResponseType::INVALID, which will result in this commitState to be rejected (not 
	// copied into the globalState) and the corresponding response type is communicated back to the
	// ParameterMaster. Be aware, that you should avoid blocking calls here. If you need blocking
	// calls, use an active trigger in combination with commit.
	return SmartACE::ParamResponseType::OK;
}

// implement your custom getter methods here
