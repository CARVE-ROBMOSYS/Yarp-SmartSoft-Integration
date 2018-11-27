#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "ExecSkill_wrap.h"
#include "BT_runner.hh"
#include "CommYARP_BT/CommTickCommand.hh"


int ExecuteSkill(const char *name)
{
    printf ("Ticking the skill: %s \n", name);

	static bool reconnected = false;
	CommYARP_BT::CommTickCommand request;
	CommYARP_BT::CommTickResult  answer;
	request.setCommand(CommYARP_BT::TickCommand::Tick);
	request.setParameter(name);

	if(!reconnected)
	{
		COMP->connectAndStartAllServices();
		reconnected = true;
	}

	Smart::StatusCode status = COMP->behaviourTreeTickQueryServiceReq->query(request, answer);		// looks like the query function does not actually block

/*
	// using query request + answer
	SmartACE::QueryId  id;
	Smart::StatusCode status = COMP->behaviourTreeTickQueryServiceReq->queryRequest(request, id);
	std::cout << "ExecuteSkill: Ticking skill " << name << " ... queryRequest return status is " << status << std::endl;

	int count = 0;
	status = Smart::SMART_NODATA;
	while(status != Smart::SMART_OK)
	{
		status = COMP->behaviourTreeTickQueryServiceReq->queryReceive(id, answer);
		sleep(0.3);
		std::cout << " Trying to get answer:  status " << status << " answer " << answer.getResult().to_string() << std::endl;
		if(status == Smart::SMART_OK)
			break;

		count++;
		if(count > 10)
			break;
	}
*/
	std::cout  << "got answer " << answer.getResult().to_string() <<  " status " << status << std::endl << std::endl;
//	sleep(10);

	return answer.getResult();
}

void ResetSkill(const char *name)
{
    printf("DUMMY Halting the skill: %s \n", name);
	return;
}
