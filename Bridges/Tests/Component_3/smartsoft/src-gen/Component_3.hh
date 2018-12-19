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
#ifndef _COMPONENT_3_HH
#define _COMPONENT_3_HH
	
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "Component_3Core.hh"
#include "Component_3Impl.hh"

// include communication objects
#include <CommYARP_BT/CommTickCommand.hh>
#include <CommYARP_BT/CommTickCommandACE.hh>
#include <CommYARP_BT/CommTickResult.hh>
#include <CommYARP_BT/CommTickResultACE.hh>

// include tasks
// include UpcallManagers

// include input-handler
// include input-handler
#include "MshHandler.hh"


// include handler
#include "CompHandler.hh"


#include "SmartStateChangeHandler.hh"

#define COMP Component_3::instance()

class Component_3 : public Component_3Core {
private:
	static Component_3 _component_3;
	
	// constructor
	Component_3();
	
	// copy-constructor
	Component_3(const Component_3& cc);
	
	// destructor
	~Component_3() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
public:
	// component
	Component_3Impl *component;
	
	
	// define tasks
	
	// define input-ports
	
	// define request-ports
	
	// define input-handler
	
	// define output-ports
	
	// define answer-ports
	Smart::IQueryServerPattern<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult,SmartACE::QueryId> *msgServer;
	Smart::QueryServerTaskTrigger<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult,SmartACE::QueryId> *msgServerInputTaskTrigger;
	
	// define request-handlers
	MshHandler *mshHandler;
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	
	
	void init(int argc, char *argv[]);
	void run();
	
	void setStartupFinished();
	Smart::StatusCode connectAndStartAllServices();
	void startAllTasks();
	void startAllTimers();
	

	// return singleton instance
	static Component_3* instance()
	{
		return (Component_3*)&_component_3;
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
		struct MsgServer_struct {
				std::string serviceName;
		} msgServer;
	
		//--- client port parameter ---
		
	} connections;
};
#endif