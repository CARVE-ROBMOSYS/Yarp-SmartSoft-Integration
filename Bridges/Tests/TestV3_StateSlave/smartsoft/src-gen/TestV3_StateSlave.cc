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
#include "TestV3_StateSlave.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"


// constructor
TestV3_StateSlave::TestV3_StateSlave()
{
	std::cout << "constructor of TestV3_StateSlave\n";
	
	component = NULL;
	
	// set all pointer members to NULL
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	
	
	// set default ini parameter values
	connections.component.name = "TestV3_StateSlave";
	connections.component.initialMainState = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
}



/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void TestV3_StateSlave::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}




/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode TestV3_StateSlave::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void TestV3_StateSlave::startAllTasks() {
}

/**
 * Start all timers contained in this component
 */
void TestV3_StateSlave::startAllTimers() {
}


Smart::TaskTriggerSubject* TestV3_StateSlave::getInputTaskTriggerFromString(const std::string &client)
{
	
	return NULL;
}


void TestV3_StateSlave::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		if(connections.component.defaultScheduler != "DEFAULT") {
			ACE_Sched_Params sched_params(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
			if(connections.component.defaultScheduler == "FIFO") {
				sched_params.policy(ACE_SCHED_FIFO);
				sched_params.priority(ACE_THR_PRI_FIFO_MIN);
			} else if(connections.component.defaultScheduler == "RR") {
				sched_params.policy(ACE_SCHED_RR);
				sched_params.priority(ACE_THR_PRI_RR_MIN);
			}
			// create new instance of the SmartSoft component with customized scheuling parameters 
			component = new TestV3_StateSlaveImpl(connections.component.name, argc, argv, sched_params);
		} else {
			// create new instance of the SmartSoft component
			component = new TestV3_StateSlaveImpl(connections.component.name, argc, argv);
		}
		
		
		std::cout << "ComponentDefinition TestV3_StateSlave is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		
		// create client ports
		
		// create InputTaskTriggers and UpcallManagers
		
		// create input-handler
		
		// create request-handlers
		
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		if (stateSlave->defineStates("MyState_1" ,"mySubState_1") != Smart::SMART_OK) std::cerr << "ERROR: defining state combinaion MyState_1.mySubState_1" << std::endl;
		if (stateSlave->defineStates("MyState_2" ,"mySubState_2") != Smart::SMART_OK) std::cerr << "ERROR: defining state combinaion MyState_2.mySubState_2" << std::endl;
		if (stateSlave->defineStates("MyState_3" ,"mySubState_3") != Smart::SMART_OK) std::cerr << "ERROR: defining state combinaion MyState_3.mySubState_3" << std::endl;
		if (stateSlave->setUpInitialState(connections.component.initialMainState) != Smart::SMART_OK) std::cerr << "ERROR: setUpInitialState" << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		
		
		
		
		// link observers with subjects
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std exception" << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}

// run the component
void TestV3_StateSlave::run()
{
	compHandler.onStartup();
	
	
	// coponent will now start running and will continue (block in the run method) until it is commanded to shutdown (i.e. by a SIGINT signal)
	component->run();
	// component was signalled to shutdown
	// 1) signall all tasks to shutdown as well (and give them 2 seconds time to cooperate)
	// if time exceeds, component is killed without further clean-up
	component->closeAllAssociatedTasks(2);
	
	if(connections.component.useLogger == true) {
		//FIXME: use logging
		//Smart::LOGGER->stopLogging();
	}
	
	compHandler.onShutdown();
	
	
	// unlink all observers
	
	// destroy all task instances

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers

	// destroy client ports

	// destroy server ports
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	

	delete stateSlave;
	// destroy state-change-handler
	delete stateChangeHandler;
	
	// destroy all master/slave ports
	delete wiringSlave;
	

	// clean-up component's internally used resources (internally used communication middleware) 
	component->cleanUpComponentResources();
	
	
	// finally delete the component itself
	delete component;
}

void TestV3_StateSlave::loadParameter(int argc, char *argv[])
{
	/*
	 Parameters can be specified via command line --filename=<filename> or -f <filename>

	 With this parameter present:
	   - The component will look for the file in the current working directory,
	     a path relative to the current directory or any absolute path
	   - The component will use the default values if the file cannot be found

	 With this parameter absent:
	   - <Name of Component>.ini will be read from current working directory, if found there
	   - $SMART_ROOT/etc/<Name of Component>.ini will be read otherwise
	   - Default values will be used if neither found in working directory or /etc
	 */
	SmartACE::SmartIniParameter parameter;
	std::ifstream parameterfile;
	bool parameterFileFound = false;

	// load parameters
	try
	{
		// if paramfile is given as argument
		if(parameter.tryAddFileFromArgs(argc,argv,"filename", 'f'))
		{
			parameterFileFound = true;
			std::cout << "parameter file is loaded from an argv argument \n";
		} else if(parameter.searchFile("TestV3_StateSlave.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load TestV3_StateSlave.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: TestV3_StateSlave.ini parameter file not found! (using default values or command line arguments)\n";
		}
		
		// add command line arguments to allow overwriting of parameters
		// from file
		parameter.addCommandLineArgs(argc,argv,"component");
		
		// initialize the naming service using the command line parameters parsed in the
		// SmartIniParameter class. The naming service parameters are expected to be in
		// the "component" parameter group.
		SmartACE::NAMING::instance()->checkForHelpArg(argc,argv);
		if(parameterFileFound) 
		{
			if(SmartACE::NAMING::instance()->init(parameter.getAllParametersFromGroup("component")) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		} else {
			if(SmartACE::NAMING::instance()->init(argc, argv) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		}
			
		// print all known parameters
		// parameter.print();
		
		//--- server port // client port // other parameter ---
		// load parameter
		parameter.getString("component", "name", connections.component.name);
		parameter.getString("component", "initialMainState", connections.component.initialMainState);
		if(parameter.checkIfParameterExists("component", "defaultScheduler")) {
			parameter.getString("component", "defaultScheduler", connections.component.defaultScheduler);
		}
		if(parameter.checkIfParameterExists("component", "useLogger")) {
			parameter.getBoolean("component", "useLogger", connections.component.useLogger);
		}
		
		
		
		
		
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}
