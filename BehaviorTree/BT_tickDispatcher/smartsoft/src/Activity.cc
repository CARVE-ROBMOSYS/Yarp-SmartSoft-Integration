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
#include "Activity.hh"
#include "BT_tickDispatcher.hh"

#include <iostream>

Activity::Activity(SmartACE::SmartComponent *comp) 
:	ActivityCore(comp)
{
	std::cout << "constructor Activity\n";
}
Activity::~Activity() 
{
	std::cout << "destructor Activity\n";
}



int Activity::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	return 0;
}

int Activity::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	// to get the incoming data, use this methods:
	Smart::StatusCode status;
	CommYARP_BT::CommTickResult answer;

	std::cout << "Hello from Activity " << std::endl;

    std::unique_lock<std::mutex> lk(COMP->mutex);
    BT_tickDispatcher *component = COMP;

    // Wait for a new message
    COMP->gotNewData.wait(lk, [component]{ std::cout << component->isNewData << " " << COMP->isNewData << std::endl;
    										return  (bool)(COMP->isNewData || COMP->isClosing) ;});


	std::cout << "NewData: " << COMP->isNewData << "  Closing: " <<  COMP->isClosing << std::endl;

    if(COMP->isClosing)
    	return -1;


    // execute the request

	CommYARP_BT::TickCommand cmd = COMP->cmd.getCommand();
	CommYARP_BT::TickResult  res = CommYARP_BT::TickResult::Error;
	std::string tickParam = COMP->cmd.getParameter();

	std::string skill = tickParam;
	auto it = COMP->tickables_map.find(skill);
	if( it == COMP->tickables_map.end())
	{
		std::cout << "Error: skill " << skill << " not found!";
		res = CommYARP_BT::TickResult::Error;
	}
	else
	{
		yDebug() << "Activity ticking " << (*it).second.tickerId << " with params " <<  (*it).second.params;
		res = (int) (*it).second.tickerInstance->tick(cmd /* (*it).second.command*/, (*it).second.params);
	}

	answer.setResult(res);
	yDebug() << "answering query id " << COMP->reqId << "  with value: " << answer.getResult().to_string() << "  (res " << (int)res << " " << res << ")\n";
	COMP->bT_Tick_input->answer(COMP->reqId, answer);

	COMP->isNewData = false;
	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int Activity::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
