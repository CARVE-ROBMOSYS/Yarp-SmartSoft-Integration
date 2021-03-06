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
#ifndef _BT_TICKDISPATCHERIMPL_HH
#define _BT_TICKDISPATCHERIMPL_HH

#include "aceSmartSoft.hh"

class BT_tickDispatcherImpl : public SmartACE::SmartComponent {
public:
	BT_tickDispatcherImpl(const std::string &componentName, int & argc, char ** argv);
	BT_tickDispatcherImpl(const std::string &componentName, int & argc, char ** argv, const ACE_Sched_Params &sched_params);
	virtual ~BT_tickDispatcherImpl();

	Smart::StatusCode run(void);
	void closeAllAssociatedTasks(const int &taskShutdownTimeLimit);
	void cleanUpComponentResources();
};

#endif
