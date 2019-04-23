/*
 * Copyright (C) 2018 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARPSMARTSOFT_ITCKER_H
#define YARPSMARTSOFT_ITCKER_H


#include <string>

#include <yarp/conf/api.h>
#include <CommYARP_BT/CommTickResult.hh>
#include <CommYARP_BT/CommTickCommand.hh>

#ifndef YARP_SmartSoft_API
#  ifdef YARP_SmartSoft_EXPORTS
#    define YARP_SmartSoft_API YARP_EXPORT
#    define YARP_SmartSoft_EXTERN YARP_EXPORT_EXTERN
#  else
#    define YARP_SmartSoft_API YARP_IMPORT
#    define YARP_SmartSoft_EXTERN YARP_IMPORT_EXTERN
#  endif
#  define YARP_SmartSoft_DEPRECATED_API YARP_DEPRECATED_API
#endif


/*
 * Interface identifying a tickable object.
 *
 */

class YARP_SmartSoft_API ITickable
{
public:

	/**
	 * Enum type listing all possible result of a tick action on the target
	 */
//	enum struct tickResult  { running, success, failure, idle, halted, error};

	/**
	 * Enum type with all the possible variant of a tick action.
	 */
	enum struct tickCommand { tick, halt };

	/**
	 * Configure the ticker by giving the required info to identify the target
	 * to be ticked. The info depend on the ticker type.
	 * @target: tick ation target identification info. For yarp it will be the
	 *          input tick port name, for SmartSoft the instance module name
	 */
	virtual bool configure(std::string target) = 0;

	/**
	 * Actually tick the target and get back a result
	 * @cmd: the command to be issued to the target. It can be one of the
	 *       tickCommand_t enum.
	 * @params: optional parameters to be sent to the target
	 */
	virtual CommYARP_BT::TickResult tick(CommYARP_BT::TickCommand cmd, std::string params, std::string skillName="skillName") = 0;
};

#endif  // YARPSMARTSOFT_ITCKER_H


