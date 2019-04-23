/*
 * Copyright (C) 2018 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARPSMARTSOFT_YARPTICKER_H
#define YARPSMARTSOFT_YARPTICKER_H


#include <yarp/os/Network.h>

#include "ITickable.h"
#include "tick_client.h"
#include <yarp/os/LogStream.h>

class YarpTicker : 	public ITickable,
					public TickClient
{
private:

	std::string target;
	yarp::os::Network yarpNetwork;
	ReturnStatusVocab a;

	void tickConvert_toYarp() {};
	CommYARP_BT::TickResult tickConvert_fromYarp(ReturnStatus in)
	{
		CommYARP_BT::TickResult ret =  CommYARP_BT::TickResult::Error;
		switch(in)
		{
			case BT_RUNNING:
			{
				ret = CommYARP_BT::TickResult::Running;
			} break;

			case BT_SUCCESS:
			{
				ret = CommYARP_BT::TickResult::Success;
			} break;

			case BT_FAILURE:
			{
				ret = CommYARP_BT::TickResult::Failure;
			} break;

			case BT_IDLE:
			{
				ret = CommYARP_BT::TickResult::Idle;
			} break;

			case BT_HALTED:
			{
				ret = CommYARP_BT::TickResult::Halted;
			} break;

			case BT_ERROR:
			default:
			{
				ret = CommYARP_BT::TickResult::Error;
			} break;

			return ret;
		}
	};

	// Inherited from BTCmd: used internally

	using TickClient::request_tick;
	using TickClient::request_status;
	using TickClient::request_halt;

public:

	YarpTicker();

	/**
	 * Configure the ticker by giving the required info to identify the target
	 * to be ticked. The info depend on the ticker type.
	 * @target: tick ation target identification info. For yarp it will be the
	 *          input tick port name, for SmartSoft the instance module name
	 */
	bool configure(std::string target) override;

	/**
	 * Actually tick the target and get back a result
	 * @cmd: the command to be issued to the target. It can be one of the
	 *       tickCommand_t enum.
	 * @params: optional parameters to be sent to the target
	 */
	CommYARP_BT::TickResult tick(CommYARP_BT::TickCommand cmd, std::string params, std::string skillName="skillName") override;
};


#endif // YARPSMARTSOFT_YARPTICKER_H


