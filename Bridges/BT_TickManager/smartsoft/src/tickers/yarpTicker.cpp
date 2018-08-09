/*
 * Copyright (C) 2018 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include "tickers/yarpTicker.h"

#include <yarp/os/Bottle.h>
#include <yarp/os/LogStream.h>

#include "BT_TickManager.hh"

using namespace std;

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


	/* Using Miccol stuff */
    BTCmd::yarp().attachAsServer(tickerPort);

	tickerPort.open(COMP->getGlobalState().getSettings().getTickManager_localPort() + target + ":o");
	yInfo() << "connecting to " << target;
	tickerPort.addOutput(target, "tcp");
	yInfo() << "DONE";

	return true;
}

/**
 * Actually tick the target and get back a result
 * @cmd: the command to be issued to the target. It can be one of the
 *       tickCommand_t enum.
 * @params: optional parameters to be sent to the target
 */
ITickable::tickResult YarpTicker::tick(tickCommand cmd, string params)
{
	BTCmd::request_tick();

	return ITickable::tickResult::running;
}


