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
#include "GenericMovementSkill.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"


// constructor
GenericMovementSkill::GenericMovementSkill()
{
	std::cout << "constructor of GenericMovementSkill\n";
	
	component = NULL;
	
	// set all pointer members to NULL
	bT_tickHandler = NULL;
	bT_tick_input = NULL;
	bT_tick_inputInputTaskTrigger = NULL;
	//coordinationPort = NULL;
	//genericMovementSkillParams = NULL;
	thread = NULL;
	threadTrigger = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	param = NULL;
	
	
	// set default ini parameter values
	connections.component.name = "GenericMovementSkill";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.bT_tick_input.serviceName = "BT_tick_input";
	connections.thread.minActFreq = 0.0;
	connections.thread.maxActFreq = 0.0;
	// scheduling default parameters
	connections.thread.scheduler = "DEFAULT";
	connections.thread.priority = -1;
	connections.thread.cpuAffinity = -1;
}



/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void GenericMovementSkill::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}




/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode GenericMovementSkill::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void GenericMovementSkill::startAllTasks() {
	// start task Thread
	if(connections.thread.scheduler != "DEFAULT") {
		ACE_Sched_Params thread_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.thread.scheduler == "FIFO") {
			thread_SchedParams.policy(ACE_SCHED_FIFO);
			thread_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.thread.scheduler == "RR") {
			thread_SchedParams.policy(ACE_SCHED_RR);
			thread_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		thread->start(thread_SchedParams, connections.thread.cpuAffinity);
	} else {
		thread->start();
	}
}

/**
 * Start all timers contained in this component
 */
void GenericMovementSkill::startAllTimers() {
}


Smart::TaskTriggerSubject* GenericMovementSkill::getInputTaskTriggerFromString(const std::string &client)
{
	
	return NULL;
}


void GenericMovementSkill::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		// print out the actual parameters which are used to initialize the component
		std::cout << " \nComponentDefinition Initial-Parameters:\n" << COMP->getGlobalState() << std::endl;
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
			component = new GenericMovementSkillImpl(connections.component.name, argc, argv, sched_params);
		} else {
			// create new instance of the SmartSoft component
			component = new GenericMovementSkillImpl(connections.component.name, argc, argv);
		}
		
		
		std::cout << "ComponentDefinition GenericMovementSkill is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		bT_tick_input = new SmartACE::QueryServer<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult>(component, connections.bT_tick_input.serviceName);
		bT_tick_inputInputTaskTrigger = new Smart::QueryServerTaskTrigger<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult,SmartACE::QueryId>(bT_tick_input);
		
		// create client ports
		
		// create InputTaskTriggers and UpcallManagers
		
		// create input-handler
		
		// create request-handlers
		bT_tickHandler = new BT_tickHandler(bT_tick_input);
		
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		status = stateSlave->setUpInitialState(connections.component.initialComponentMode);
		if (status != Smart::SMART_OK) std::cerr << status << "; failed setting initial ComponentMode: " << connections.component.initialComponentMode << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		
		// create parameter slave
		param = new SmartACE::ParameterSlave(component, &paramHandler);
		
		
		// create Task Thread
		thread = new Thread(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		if(connections.thread.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.thread.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(thread);
				component->getTimerManager()->scheduleTimer(triggerPtr, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				threadTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task Thread" << std::endl;
			}
		} else if(connections.thread.trigger == "DataTriggered") {
			threadTrigger = getInputTaskTriggerFromString(connections.thread.inPortRef);
			if(threadTrigger != NULL) {
				threadTrigger->attach(thread, connections.thread.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.thread.inPortRef << " as activation source for Task Thread" << std::endl;
			}
		} 
		
		
		// link observers with subjects
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std exception" << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}

// run the component
void GenericMovementSkill::run()
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
	// unlink all UpcallManagers
	// unlink the TaskTrigger
	threadTrigger->detach(thread);
	delete thread;

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers

	// destroy client ports

	// destroy server ports
	delete bT_tick_input;
	delete bT_tick_inputInputTaskTrigger;
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	delete bT_tickHandler;
	

	delete stateSlave;
	// destroy state-change-handler
	delete stateChangeHandler;
	
	// destroy all master/slave ports
	delete wiringSlave;
	delete param;
	

	// clean-up component's internally used resources (internally used communication middleware) 
	component->cleanUpComponentResources();
	
	
	// finally delete the component itself
	delete component;
}

void GenericMovementSkill::loadParameter(int argc, char *argv[])
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
		} else if(parameter.searchFile("GenericMovementSkill.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load GenericMovementSkill.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: GenericMovementSkill.ini parameter file not found! (using default values or command line arguments)\n";
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
		parameter.getString("component", "initialComponentMode", connections.component.initialComponentMode);
		if(parameter.checkIfParameterExists("component", "defaultScheduler")) {
			parameter.getString("component", "defaultScheduler", connections.component.defaultScheduler);
		}
		if(parameter.checkIfParameterExists("component", "useLogger")) {
			parameter.getBoolean("component", "useLogger", connections.component.useLogger);
		}
		
		
		
		// load parameters for server BT_tick_input
		parameter.getString("BT_tick_input", "serviceName", connections.bT_tick_input.serviceName);
		
		// load parameters for task Thread
		parameter.getDouble("Thread", "minActFreqHz", connections.thread.minActFreq);
		parameter.getDouble("Thread", "maxActFreqHz", connections.thread.maxActFreq);
		parameter.getString("Thread", "triggerType", connections.thread.trigger);
		if(connections.thread.trigger == "PeriodicTimer") {
			parameter.getDouble("Thread", "periodicActFreqHz", connections.thread.periodicActFreq);
		} else if(connections.thread.trigger == "DataTriggered") {
			parameter.getString("Thread", "inPortRef", connections.thread.inPortRef);
			parameter.getInteger("Thread", "prescale", connections.thread.prescale);
		}
		if(parameter.checkIfParameterExists("Thread", "scheduler")) {
			parameter.getString("Thread", "scheduler", connections.thread.scheduler);
		}
		if(parameter.checkIfParameterExists("Thread", "priority")) {
			parameter.getInteger("Thread", "priority", connections.thread.priority);
		}
		if(parameter.checkIfParameterExists("Thread", "cpuAffinity")) {
			parameter.getInteger("Thread", "cpuAffinity", connections.thread.cpuAffinity);
		}
		
		paramHandler.loadParameter(parameter);
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}
