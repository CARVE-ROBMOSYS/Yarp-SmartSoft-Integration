/*
 * Copyright (C) 2018 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARPSMARTSOFT_GOALTICKER_H
#define YARPSMARTSOFT_GOALTICKER_H

#include <string>
#include <vector>
#include <list>

#include "aceSmartSoft.hh"

#include "ITickable.h"

class GoalTicker : public ITickable
{
private:
	SmartACE::StateMaster *stateMaster;
	std::list<std::string> mainstates;
	std::string targetSkill;

public:

	GoalTicker(SmartACE::StateMaster *_stateMaster);		// TBD: if we want this to be a plugin, this praram in the constructor shall be removed

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


#endif // YARPSMARTSOFT_SMARTTICKER_H


