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
#include "BTCmd.h"

// From miccol definition
enum ReturnStatus {BT_RUNNING, BT_SUCCESS, BT_FAILURE, BT_IDLE, BT_HALTED, BT_ERROR};

class YarpTicker : 	public ITickable,
					public BTCmd
{
private:
	yarp::os::Network yarpNetwork;
	yarp::os::Port    tickerPort;

	void tickConvert_toYarp() {};
	tickResult tickConvert_fromYarp(ReturnStatus in)
	{
		tickResult ret =  ITickable::tickResult::fatal_error;
		switch(in)
		{
			case BT_RUNNING:
			{
				ret = ITickable::tickResult::running;
			} break;

			case BT_SUCCESS:
			{

			} break;

			case BT_FAILURE:
			{

			} break;

			case BT_IDLE:
			{

			} break;

			case BT_HALTED:
			{

			} break;

			case BT_ERROR:
			{

			} break;

			return ret;
		}
	};
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
	tickResult tick(tickCommand cmd, std::string params) override;

	/* Inherited from BTCmd:

	  virtual int32_t request_tick();
	  virtual int32_t request_status();
	  virtual void request_halt();
	 */
};


#endif // YARPSMARTSOFT_YARPTICKER_H


