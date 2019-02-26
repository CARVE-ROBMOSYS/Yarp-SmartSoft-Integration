/*
 * Copyright (C) 2018 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include "tickers/yarpTicker.h"

#include <yarp/os/Bottle.h>
#include <yarp/os/LogStream.h>

#include "BT_tickDispatcher.hh"

using namespace std;
using namespace CommYARP_BT;

YarpTicker::YarpTicker()
{

}

/*
 * Configure the ticker by giving the required info to identify the target
 * to be ticked. The info depend on the ticker type.
 * @target: tick action target identification info. For yarp it will be the
 *          input tick port name, for SmartSoft the instance module name
 */
bool YarpTicker::configure(std::string target)
{
	// Check yarp network
	if(!yarpNetwork.checkNetwork(2))
	{
		yError("Cannot find YARP network, is the yarpserver running and reachable?");
		return false;
	}

	TickClient::configure(COMP->getGlobalState().getSettings().getTickManager_localPort() + target);

	yInfo() << "connecting to " << target;
	if(!TickClient::connect(target))
		yError() << " Cannot connect to " << target;

	yInfo() << "DONE";
	return true;
}

/**
 * Actually tick the target and get back a result
 * @cmd: the command to be issued to the target. It can be one of the
 *       tickCommand_t enum.
 * @params: optional parameters to be sent to the target
 */
CommYARP_BT::TickResult YarpTicker::tick(CommYARP_BT::TickCommand cmd, string params)
{
	int tmpRet;
	if(cmd == TickCommand::Tick)
	{
		std::cout << "\t YarpTicker ticking " << params << "... ";
		tmpRet = request_tick(params);
	}

	if(cmd == TickCommand::Halt)
	{
		std::cout << "\t YarpTicker halting " << params << "... ";
		tmpRet = request_halt();
		std::cout << "\t request_tick  " << (int) tmpRet << std::endl;
	}

	TickResult res = tickConvert_fromYarp( (ReturnStatus)tmpRet);
	std::cout << "\t request_tick  " << (int) tmpRet << std::endl;
	std::cout << "\tret SS  " << (int) res << "  " << res.to_string() << std::endl;

	return res;
}


