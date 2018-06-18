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
#include "UpdateThread.hh"
#include "BridgeV3_FromYarp_BaseStateService.hh"

#include <iostream>
#include <yarp/os/LogStream.h>
#include <yarp/math/FrameTransform.h>


UpdateThread::UpdateThread(SmartACE::SmartComponent *comp) 
:	UpdateThreadCore(comp)
{
	std::cout << "constructor UpdateThread\n";
}

UpdateThread::~UpdateThread() 
{
	std::cout << "destructor UpdateThread\n";
}

int UpdateThread::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	return 0;
}

int UpdateThread::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	// to get the incoming data, use this methods:
	Smart::StatusCode status;

	std::cout << "Hello from UpdateThread " << std::endl;

	if(!COMP->iFrame)
		return 0;

	yarp::sig::Matrix mat;
	std::string  fromRef("/from"), toRef("/to");
	if(!COMP->iFrame->getTransform(fromRef, toRef, mat) )
	{
		yError() << "Cannot get requested transformation from " << fromRef << " to " << toRef;
	}

	CommBasicObjects::CommBaseState commCurrentBaseState;
	CommBasicObjects::CommBasePose pose;

	yarp::sig::Vector rpy;
	yarp::math::FrameTransform tmp;

	tmp.fromMatrix(mat);
	rpy = tmp.getRPYRot();

	pose.set_base_roll(rpy[0]);
	pose.set_base_elevation(rpy[1]);
	pose.set_base_azimuth(rpy[2]);


/*
	// get base pose and velocity from gazebo interface
	commCurrentBaseState.set_base_position();
	commCurrentBaseState.set_base_raw_position(COMP->pose->getBasePose());
	commCurrentBaseState.set_base_velocity(COMP->velocity->getBaseVelocity());

	CommBasicObjects::CommTimeStamp time_stamp;
	time_stamp.set_now();
	commCurrentBaseState.set_time_stamp(time_stamp);
*/
	// publish pose-update
	this->baseStateServiceOutPut(commCurrentBaseState);

	yarp::os::Time::delay(COMP->COMP->getGlobalState().getSettings().getPeriod());
	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}

int UpdateThread::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
