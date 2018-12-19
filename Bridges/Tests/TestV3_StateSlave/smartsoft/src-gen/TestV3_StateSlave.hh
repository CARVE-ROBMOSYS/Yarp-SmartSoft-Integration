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
#ifndef _TESTV3_STATESLAVE_HH
#define _TESTV3_STATESLAVE_HH
	
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "TestV3_StateSlaveCore.hh"
#include "TestV3_StateSlaveImpl.hh"

// include communication objects

// include tasks
// include UpcallManagers

// include input-handler
// include input-handler


// include handler
#include "CompHandler.hh"


#include "SmartStateChangeHandler.hh"

#define COMP TestV3_StateSlave::instance()

class TestV3_StateSlave : public TestV3_StateSlaveCore {
private:
	static TestV3_StateSlave _testV3_StateSlave;
	
	// constructor
	TestV3_StateSlave();
	
	// copy-constructor
	TestV3_StateSlave(const TestV3_StateSlave& cc);
	
	// destructor
	~TestV3_StateSlave() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
public:
	// component
	TestV3_StateSlaveImpl *component;
	
	
	// define tasks
	
	// define input-ports
	
	// define request-ports
	
	// define input-handler
	
	// define output-ports
	
	// define answer-ports
	
	// define request-handlers
	
	
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
	static TestV3_StateSlave* instance()
	{
		return (TestV3_StateSlave*)&_testV3_StateSlave;
	}
	
	// connections parameter
	struct connections_struct
	{
		// component struct
		struct component_struct
		{
			// the name of the component
			std::string name;
			std::string initialMainState;
			std::string defaultScheduler;
			bool useLogger;
		} component;
		
		//--- task parameter ---
		
		//--- upcall parameter ---
		
		//--- server port parameter ---
	
		//--- client port parameter ---
		
	} connections;
};
#endif
