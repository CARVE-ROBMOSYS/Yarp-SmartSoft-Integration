//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Christian Schlegel (schlegel@hs-ulm.de)
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
#include "ReaderTask.hh"
#include "DummySubscriber.hh"

#include <iostream>

ReaderTask::ReaderTask(CHS::SmartComponent *comp) 
:	ReaderTaskCore(comp)
{
	std::cout << "constructor ReaderTask\n";
}
ReaderTask::~ReaderTask() 
{
	std::cout << "destructor ReaderTask\n";
}


int ReaderTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	return 0;
}
int ReaderTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	std::cout << "Hello from ReaderTask\n";

	DummyData::CommDummy  dataIn;
	CHS::StatusCode ret = COMP->positionSubscriber->getUpdate(dataIn);

	std::string retCode = StatusCodeConversion(ret);

	std::stringstream  ss;
	dataIn.to_ostream(ss);
	std::cout << "Read " << ss.str() << " \nRet code " << retCode << std::endl;

	sleep(1);
	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int ReaderTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
