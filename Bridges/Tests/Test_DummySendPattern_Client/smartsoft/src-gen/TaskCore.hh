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
#ifndef _TASK_CORE_HH
#define _TASK_CORE_HH
	
#include "aceSmartSoft.hh"

// include upcall interface

// include communication-objects for output ports
#include <CommBasicObjects/CommBaseState.hh>

	
class TaskCore
:	public SmartACE::ManagedTask
{
private:
	bool useDefaultState; 
	bool useLogging;
	int taskLoggingId;
	unsigned int currentUpdateCount;
	
	
	
protected:
	virtual int execute_protected_region();
	
	virtual void updateAllCommObjects();
	
	virtual int getPreviousCommObjId();
	
	void triggerLogEntry(const int& idOffset);
	
	
	
	// this method is meant to be used in derived classes
	Smart::StatusCode baseStateServiceOutPut(CommBasicObjects::CommBaseState &baseStateServiceOutDataObject);

public:
	TaskCore(Smart::IComponent *comp, const bool &useDefaultState=true)
	:	SmartACE::ManagedTask(comp)
	,	useDefaultState(useDefaultState)
	,	useLogging(false)
	,	taskLoggingId(0)
	,	currentUpdateCount(0)
	{  }
	virtual ~TaskCore()
	{  }
	
	inline void setUpLogging(const int &taskNbr, const bool &useLogging=true) {
		this->taskLoggingId = taskNbr;
		this->useLogging = useLogging;
	}
	
	inline bool isLoggingActive() const {
		return useLogging;
	}
	
	inline int getLoggingID() const {
		return taskLoggingId;
	}
	
	inline int getCurrentUpdateCount() const {
		return currentUpdateCount;
	}
};
#endif
