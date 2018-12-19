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
#include "BT_tickDispatcher.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"


// constructor
BT_tickDispatcher::BT_tickDispatcher()
{
	std::cout << "constructor of BT_tickDispatcher\n";
	
	component = NULL;
	
	// set all pointer members to NULL
	activity = NULL;
	activityTrigger = NULL;
	bT_Navig_tick = NULL;
	bT_Tick_Query_Handler = NULL;
	bT_Tick_input = NULL;
	bT_Tick_inputInputTaskTrigger = NULL;
	bT_manip_tick = NULL;
	//bT_tickDispatcherParams = NULL;
	bT_vision_tick = NULL;
	//coordinationPort = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	param = NULL;
	
	
	// set default ini parameter values
	connections.component.name = "BT_tickDispatcher";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.bT_Tick_input.serviceName = "BT_Tick_input";
	connections.bT_Navig_tick.initialConnect = false;
	connections.bT_Navig_tick.wiringName = "BT_Navig_tick";
	connections.bT_Navig_tick.serverName = "unknown";
	connections.bT_Navig_tick.serviceName = "unknown";
	connections.bT_Navig_tick.interval = 1;
	connections.bT_manip_tick.initialConnect = false;
	connections.bT_manip_tick.wiringName = "BT_manip_tick";
	connections.bT_manip_tick.serverName = "unknown";
	connections.bT_manip_tick.serviceName = "unknown";
	connections.bT_manip_tick.interval = 1;
	connections.bT_vision_tick.initialConnect = false;
	connections.bT_vision_tick.wiringName = "BT_vision_tick";
	connections.bT_vision_tick.serverName = "unknown";
	connections.bT_vision_tick.serviceName = "unknown";
	connections.bT_vision_tick.interval = 1;
	connections.activity.minActFreq = 0.0;
	connections.activity.maxActFreq = 0.0;
	// scheduling default parameters
	connections.activity.scheduler = "DEFAULT";
	connections.activity.priority = -1;
	connections.activity.cpuAffinity = -1;
}



/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void BT_tickDispatcher::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}


Smart::StatusCode BT_tickDispatcher::connectBT_Navig_tick(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.bT_Navig_tick.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = bT_Navig_tick->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->bT_Navig_tick->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	return status;
}
Smart::StatusCode BT_tickDispatcher::connectBT_manip_tick(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.bT_manip_tick.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = bT_manip_tick->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->bT_manip_tick->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	return status;
}
Smart::StatusCode BT_tickDispatcher::connectBT_vision_tick(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.bT_vision_tick.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = bT_vision_tick->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->bT_vision_tick->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	return status;
}


/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode BT_tickDispatcher::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	status = connectBT_Navig_tick(connections.bT_Navig_tick.serverName, connections.bT_Navig_tick.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectBT_manip_tick(connections.bT_manip_tick.serverName, connections.bT_manip_tick.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectBT_vision_tick(connections.bT_vision_tick.serverName, connections.bT_vision_tick.serviceName);
	if(status != Smart::SMART_OK) return status;
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void BT_tickDispatcher::startAllTasks() {
	// start task Activity
	if(connections.activity.scheduler != "DEFAULT") {
		ACE_Sched_Params activity_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.activity.scheduler == "FIFO") {
			activity_SchedParams.policy(ACE_SCHED_FIFO);
			activity_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.activity.scheduler == "RR") {
			activity_SchedParams.policy(ACE_SCHED_RR);
			activity_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		activity->start(activity_SchedParams, connections.activity.cpuAffinity);
	} else {
		activity->start();
	}
}

/**
 * Start all timers contained in this component
 */
void BT_tickDispatcher::startAllTimers() {
}


Smart::TaskTriggerSubject* BT_tickDispatcher::getInputTaskTriggerFromString(const std::string &client)
{
	
	return NULL;
}


void BT_tickDispatcher::init(int argc, char *argv[])
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
			component = new BT_tickDispatcherImpl(connections.component.name, argc, argv, sched_params);
		} else {
			// create new instance of the SmartSoft component
			component = new BT_tickDispatcherImpl(connections.component.name, argc, argv);
		}
		
		
		std::cout << "ComponentDefinition BT_tickDispatcher is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		bT_Tick_input = new SmartACE::QueryServer<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult>(component, connections.bT_Tick_input.serviceName);
		bT_Tick_inputInputTaskTrigger = new Smart::QueryServerTaskTrigger<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult,SmartACE::QueryId>(bT_Tick_input);
		
		// create client ports
		bT_Navig_tick = new SmartACE::QueryClient<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult>(component);
		bT_manip_tick = new SmartACE::QueryClient<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult>(component);
		bT_vision_tick = new SmartACE::QueryClient<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult>(component);
		
		// create InputTaskTriggers and UpcallManagers
		
		// create input-handler
		
		// create request-handlers
		bT_Tick_Query_Handler = new BT_Tick_Query_Handler(bT_Tick_input);
		
		
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
		dynamic_cast<SmartACE::QueryClient<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult>*>(bT_Navig_tick)->add(wiringSlave, connections.bT_Navig_tick.wiringName);
		dynamic_cast<SmartACE::QueryClient<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult>*>(bT_manip_tick)->add(wiringSlave, connections.bT_manip_tick.wiringName);
		dynamic_cast<SmartACE::QueryClient<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult>*>(bT_vision_tick)->add(wiringSlave, connections.bT_vision_tick.wiringName);
		
		// create parameter slave
		param = new SmartACE::ParameterSlave(component, &paramHandler);
		
		
		// create Task Activity
		activity = new Activity(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		if(connections.activity.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.activity.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(activity);
				component->getTimerManager()->scheduleTimer(triggerPtr, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				activityTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task Activity" << std::endl;
			}
		} else if(connections.activity.trigger == "DataTriggered") {
			activityTrigger = getInputTaskTriggerFromString(connections.activity.inPortRef);
			if(activityTrigger != NULL) {
				activityTrigger->attach(activity, connections.activity.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.activity.inPortRef << " as activation source for Task Activity" << std::endl;
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
void BT_tickDispatcher::run()
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
	activityTrigger->detach(activity);
	delete activity;

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers

	// destroy client ports
	delete bT_Navig_tick;
	delete bT_manip_tick;
	delete bT_vision_tick;

	// destroy server ports
	delete bT_Tick_input;
	delete bT_Tick_inputInputTaskTrigger;
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	delete bT_Tick_Query_Handler;
	

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

void BT_tickDispatcher::loadParameter(int argc, char *argv[])
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
		} else if(parameter.searchFile("BT_tickDispatcher.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load BT_tickDispatcher.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: BT_tickDispatcher.ini parameter file not found! (using default values or command line arguments)\n";
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
		
		// load parameters for client BT_Navig_tick
		parameter.getBoolean("BT_Navig_tick", "initialConnect", connections.bT_Navig_tick.initialConnect);
		parameter.getString("BT_Navig_tick", "serviceName", connections.bT_Navig_tick.serviceName);
		parameter.getString("BT_Navig_tick", "serverName", connections.bT_Navig_tick.serverName);
		parameter.getString("BT_Navig_tick", "wiringName", connections.bT_Navig_tick.wiringName);
		// load parameters for client BT_manip_tick
		parameter.getBoolean("BT_manip_tick", "initialConnect", connections.bT_manip_tick.initialConnect);
		parameter.getString("BT_manip_tick", "serviceName", connections.bT_manip_tick.serviceName);
		parameter.getString("BT_manip_tick", "serverName", connections.bT_manip_tick.serverName);
		parameter.getString("BT_manip_tick", "wiringName", connections.bT_manip_tick.wiringName);
		// load parameters for client BT_vision_tick
		parameter.getBoolean("BT_vision_tick", "initialConnect", connections.bT_vision_tick.initialConnect);
		parameter.getString("BT_vision_tick", "serviceName", connections.bT_vision_tick.serviceName);
		parameter.getString("BT_vision_tick", "serverName", connections.bT_vision_tick.serverName);
		parameter.getString("BT_vision_tick", "wiringName", connections.bT_vision_tick.wiringName);
		
		
		// load parameters for server BT_Tick_input
		parameter.getString("BT_Tick_input", "serviceName", connections.bT_Tick_input.serviceName);
		
		// load parameters for task Activity
		parameter.getDouble("Activity", "minActFreqHz", connections.activity.minActFreq);
		parameter.getDouble("Activity", "maxActFreqHz", connections.activity.maxActFreq);
		parameter.getString("Activity", "triggerType", connections.activity.trigger);
		if(connections.activity.trigger == "PeriodicTimer") {
			parameter.getDouble("Activity", "periodicActFreqHz", connections.activity.periodicActFreq);
		} else if(connections.activity.trigger == "DataTriggered") {
			parameter.getString("Activity", "inPortRef", connections.activity.inPortRef);
			parameter.getInteger("Activity", "prescale", connections.activity.prescale);
		}
		if(parameter.checkIfParameterExists("Activity", "scheduler")) {
			parameter.getString("Activity", "scheduler", connections.activity.scheduler);
		}
		if(parameter.checkIfParameterExists("Activity", "priority")) {
			parameter.getInteger("Activity", "priority", connections.activity.priority);
		}
		if(parameter.checkIfParameterExists("Activity", "cpuAffinity")) {
			parameter.getInteger("Activity", "cpuAffinity", connections.activity.cpuAffinity);
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