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
#include "CompHandler.hh"
#include "YarpNavigationClient.hh"

#include <iostream>

#include <yarp/os/LogStream.h>

// include communication objects


void CompHandler::onStartup() 
{
	std::cout << "startup - put your startupCode in CompHandler::onStartup()!!!\n";
	Smart::StatusCode status;


	// Check yarp network
	if(!COMP->yarp.checkNetwork(2))
	{
		std::cerr << "Cannot find YARP network, is the yarpserver running and reachable?";
		throw std::runtime_error("Cannot find YARP network, is the yarpserver running and reachable?");
	}

	//
	// Get data from config file
	//
//	std::string map_server_name 		 = COMP->getGlobalState().getSettings().getMap_server_name();
//	std::string navigation_server_name 	 = COMP->getGlobalState().getSettings().getNavigation_server_name();
//	std::string localization_server_name = COMP->getGlobalState().getSettings().getLocalization_server_name();

    yarp::os::Property        navigClientCfg;
    navigClientCfg.put("device", "navigation2DClient");
    navigClientCfg.put("local", "/SmartSoft/robotPathPlanner");
    navigClientCfg.put("navigation_server", "/navigationServer");
    navigClientCfg.put("map_locations_server", "/mapServer");
    navigClientCfg.put("localization_server", "/localizationServer");

	yDebug() << "Opening navigation client!!!";

	//
	// Open navigation client
	//
	if(!COMP->navClient.open(navigClientCfg))
	{
		std::string errorStr = " Failed opening the navigation client, is the server running?";
		COMP->navClient.close();
		throw std::invalid_argument(errorStr);
	}

	COMP->navClient.view(COMP->iNav);
	if(COMP->iNav == nullptr)
	{
		std::string errorStr = "Cannot get navigation interface from navigation client";
		COMP->navClient.close();
		throw std::invalid_argument(errorStr);
	}

	yInfo() << "Navigation client successfully initialized";

	std::vector<std::string> locations;
	COMP->iNav->getLocationsList(locations);
	std::cout << locations.size() << std::endl;

	for(int i=0; i<locations.size(); i++)
		std::cout << locations[i] << std::endl;


	// open configuration ports
	COMP->pathPlanner_port.open("/SmartSoft/navigClient/pathPlanner/rpc");
	COMP->goTo_port.open("/SmartSoft/navigClient/goTo/rpc");

	bool conn = yarp::os::Network::connect(COMP->pathPlanner_port.getName(), "/robotPathPlanner/rpc");
	conn &= yarp::os::Network::connect(COMP->goTo_port.getName(), "/robotGoto/rpc");

	if(!conn)
	{
		std::string errorStr = " Cannot connect to pathPlanner or robotGoTo RPC ports";
		COMP->navClient.close();
		throw std::invalid_argument(errorStr);
	}

	yInfo() << "Connections to navigation RPCs done!";

	// Start all services. If you need manual control, use the content of this function to
	// connect and start each service individually, e.g:
	// COMP->connectMyPortName("SmartExampleComponent", "examplePort");
	status = COMP->connectAndStartAllServices();
	
	// Start all tasks. If you need manual control, use the content of this function to
	// start each task individually.
	COMP->startAllTasks();
	
	// Start all timers. If you need manual control, use the content of this function to
	// start each timer individually.
	COMP->startAllTimers();
	
	// Notify the component that setup/initialization is finished.
	// You may move this function to any other place.
	COMP->setStartupFinished(); 

	COMP->initialized = true;
}

void CompHandler::onShutdown() 
{
	std::cout << "shutdown - put your cleanup code in CompHandler::onShutdown()!!!\n";
	COMP->navClient.close();
}


