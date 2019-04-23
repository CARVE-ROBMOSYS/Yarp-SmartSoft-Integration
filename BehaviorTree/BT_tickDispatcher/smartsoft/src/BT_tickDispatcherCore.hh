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
#ifndef _BT_TICKDISPATCHERCORE_HH
#define _BT_TICKDISPATCHERCORE_HH
	
#include <map>
#include <tuple>
#include <iostream>

#include "aceSmartSoft.hh"

#include "tickers/ITickable.h"
#include "tickers/yarpTicker.h"
#include "tickers/SmartTicker.h"
#include <yarp/os/Port.h>

typedef struct
{
	std::string skill2Tick;
	std::string tickerType;
	std::string tickerId;
	std::string command;  // this should be enum
	std::string params;
	ITickable* tickerInstance;
} Info;

class BT_tickDispatcherCore
{
public:
	SmartACE::StateMaster *stateMaster;
	SmartACE::ParameterMaster *paramMaster;			// To remotely change parameters on skills

	std::map<std::string, Info >  tickables_map;

	// keep track of what has been instantiated
	std::list<YarpTicker  *> yarpTickers_list;
	std::list<ITickable *> smartTickers_list;

	CommYARP_BT::CommTickCommand cmd;
	int reqId;
	std::mutex mutex;
	std::atomic<bool> isNewData {false};
	std::atomic<bool> isClosing {false};
	std::condition_variable gotNewData;

	yarp::os::Port debugPort;
	yarp::os::Port blackboardPort;
//	std::map<std::pair<std::string, std::string>, InfoInit >  tickables_map_init;   // serve davvero? per verificare in creazione se un ticker c'è già o meno...

public:
	BT_tickDispatcherCore();
};
	
#endif
