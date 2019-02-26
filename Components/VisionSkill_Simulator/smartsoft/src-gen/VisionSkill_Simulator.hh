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
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#ifndef _VISIONSKILL_SIMULATOR_HH
#define _VISIONSKILL_SIMULATOR_HH
	
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "VisionSkill_SimulatorCore.hh"
#include "VisionSkill_SimulatorImpl.hh"

// include communication objects
#include <CommYARP_BT/CommTickCommand.hh>
#include <CommYARP_BT/CommTickCommandACE.hh>
#include <CommYARP_BT/CommTickResult.hh>
#include <CommYARP_BT/CommTickResultACE.hh>

// include tasks
// include UpcallManagers

// include input-handler
// include input-handler
#include "TickHandler.hh"


// include handler
#include "CompHandler.hh"

#include "ParameterStateStruct.hh"
#include "ParameterUpdateHandler.hh"

#include "SmartStateChangeHandler.hh"

#define COMP VisionSkill_Simulator::instance()

class VisionSkill_Simulator : public VisionSkill_SimulatorCore {
private:
	static VisionSkill_Simulator _visionSkill_Simulator;
	
	// constructor
	VisionSkill_Simulator();
	
	// copy-constructor
	VisionSkill_Simulator(const VisionSkill_Simulator& cc);
	
	// destructor
	~VisionSkill_Simulator() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
public:
	// component
	VisionSkill_SimulatorImpl *component;
	
	ParameterStateStruct getGlobalState() const
	{
		return paramHandler.getGlobalState();
	}
	
	// define tasks
	
	// define input-ports
	
	// define request-ports
	
	// define input-handler
	
	// define output-ports
	
	// define answer-ports
	Smart::IQueryServerPattern<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult,SmartACE::QueryId> *tickInput;
	Smart::QueryServerTaskTrigger<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult,SmartACE::QueryId> *tickInputInputTaskTrigger;
	
	// define request-handlers
	TickHandler *tickHandler;
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	ParamUpdateHandler paramHandler;
	SmartACE::ParameterSlave *param;
	
	
	void init(int argc, char *argv[]);
	void run();
	
	void setStartupFinished();
	Smart::StatusCode connectAndStartAllServices();
	void startAllTasks();
	void startAllTimers();
	

	// return singleton instance
	static VisionSkill_Simulator* instance()
	{
		return (VisionSkill_Simulator*)&_visionSkill_Simulator;
	}
	
	// connections parameter
	struct connections_struct
	{
		// component struct
		struct component_struct
		{
			// the name of the component
			std::string name;
			std::string initialComponentMode;
			std::string defaultScheduler;
			bool useLogger;
		} component;
		
		//--- task parameter ---
		
		//--- upcall parameter ---
		
		//--- server port parameter ---
		struct TickInput_struct {
				std::string serviceName;
		} tickInput;
	
		//--- client port parameter ---
		
	} connections;
};
#endif
