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
#include "BT_runner.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"


// constructor
BT_runner::BT_runner()
{
	std::cout << "constructor of BT_runner\n";
	
	component = NULL;
	
	// set all pointer members to NULL
	behaviourTreeTickQueryServiceReq = NULL;
	task1 = NULL;
	task1Trigger = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	
	
	// set default ini parameter values
	connections.component.name = "BT_runner";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.behaviourTreeTickQueryServiceReq.initialConnect = false;
	connections.behaviourTreeTickQueryServiceReq.wiringName = "BehaviourTreeTickQueryServiceReq";
	connections.behaviourTreeTickQueryServiceReq.serverName = "unknown";
	connections.behaviourTreeTickQueryServiceReq.serviceName = "unknown";
	connections.behaviourTreeTickQueryServiceReq.interval = 1;
	connections.task1.minActFreq = 0.0;
	connections.task1.maxActFreq = 0.0;
	// scheduling default parameters
	connections.task1.scheduler = "DEFAULT";
	connections.task1.priority = -1;
	connections.task1.cpuAffinity = -1;
}



/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void BT_runner::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}


Smart::StatusCode BT_runner::connectBehaviourTreeTickQueryServiceReq(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.behaviourTreeTickQueryServiceReq.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = behaviourTreeTickQueryServiceReq->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->behaviourTreeTickQueryServiceReq->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	return status;
}


/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode BT_runner::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	status = connectBehaviourTreeTickQueryServiceReq(connections.behaviourTreeTickQueryServiceReq.serverName, connections.behaviourTreeTickQueryServiceReq.serviceName);
	if(status != Smart::SMART_OK) return status;
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void BT_runner::startAllTasks() {
	// start task Task1
	if(connections.task1.scheduler != "DEFAULT") {
		ACE_Sched_Params task1_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.task1.scheduler == "FIFO") {
			task1_SchedParams.policy(ACE_SCHED_FIFO);
			task1_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.task1.scheduler == "RR") {
			task1_SchedParams.policy(ACE_SCHED_RR);
			task1_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		task1->start(task1_SchedParams, connections.task1.cpuAffinity);
	} else {
		task1->start();
	}
}

/**
 * Start all timers contained in this component
 */
void BT_runner::startAllTimers() {
}


Smart::TaskTriggerSubject* BT_runner::getInputTaskTriggerFromString(const std::string &client)
{
	
	return NULL;
}


void BT_runner::init(int argc, char *argv[])
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
			component = new BT_runnerImpl(connections.component.name, argc, argv, sched_params);
		} else {
			// create new instance of the SmartSoft component
			component = new BT_runnerImpl(connections.component.name, argc, argv);
		}
		
		
		std::cout << "ComponentDefinition BT_runner is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		
		// create client ports
		behaviourTreeTickQueryServiceReq = new SmartACE::QueryClient<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult>(component);
		
		// create InputTaskTriggers and UpcallManagers
		
		// create input-handler
		
		// create request-handlers
		
		
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
		dynamic_cast<SmartACE::QueryClient<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult>*>(behaviourTreeTickQueryServiceReq)->add(wiringSlave, connections.behaviourTreeTickQueryServiceReq.wiringName);
		
		
		
		// create Task Task1
		task1 = new Task1(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		if(connections.task1.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.task1.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(task1);
				component->getTimerManager()->scheduleTimer(triggerPtr, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				task1Trigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task Task1" << std::endl;
			}
		} else if(connections.task1.trigger == "DataTriggered") {
			task1Trigger = getInputTaskTriggerFromString(connections.task1.inPortRef);
			if(task1Trigger != NULL) {
				task1Trigger->attach(task1, connections.task1.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.task1.inPortRef << " as activation source for Task Task1" << std::endl;
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
void BT_runner::run()
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
	task1Trigger->detach(task1);
	delete task1;

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers

	// destroy client ports
	delete behaviourTreeTickQueryServiceReq;

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

void BT_runner::loadParameter(int argc, char *argv[])
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
		} else if(parameter.searchFile("BT_runner.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load BT_runner.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: BT_runner.ini parameter file not found! (using default values or command line arguments)\n";
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
		
		// load parameters for client BehaviourTreeTickQueryServiceReq
		parameter.getBoolean("BehaviourTreeTickQueryServiceReq", "initialConnect", connections.behaviourTreeTickQueryServiceReq.initialConnect);
		parameter.getString("BehaviourTreeTickQueryServiceReq", "serviceName", connections.behaviourTreeTickQueryServiceReq.serviceName);
		parameter.getString("BehaviourTreeTickQueryServiceReq", "serverName", connections.behaviourTreeTickQueryServiceReq.serverName);
		parameter.getString("BehaviourTreeTickQueryServiceReq", "wiringName", connections.behaviourTreeTickQueryServiceReq.wiringName);
		
		
		
		// load parameters for task Task1
		parameter.getDouble("Task1", "minActFreqHz", connections.task1.minActFreq);
		parameter.getDouble("Task1", "maxActFreqHz", connections.task1.maxActFreq);
		parameter.getString("Task1", "triggerType", connections.task1.trigger);
		if(connections.task1.trigger == "PeriodicTimer") {
			parameter.getDouble("Task1", "periodicActFreqHz", connections.task1.periodicActFreq);
		} else if(connections.task1.trigger == "DataTriggered") {
			parameter.getString("Task1", "inPortRef", connections.task1.inPortRef);
			parameter.getInteger("Task1", "prescale", connections.task1.prescale);
		}
		if(parameter.checkIfParameterExists("Task1", "scheduler")) {
			parameter.getString("Task1", "scheduler", connections.task1.scheduler);
		}
		if(parameter.checkIfParameterExists("Task1", "priority")) {
			parameter.getInteger("Task1", "priority", connections.task1.priority);
		}
		if(parameter.checkIfParameterExists("Task1", "cpuAffinity")) {
			parameter.getInteger("Task1", "cpuAffinity", connections.task1.cpuAffinity);
		}
		
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}
