#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "ExecSkill_wrap.h"
#include "BT_runner.hh"
#include "CommYARP_BT/CommTickCommand.hh"

enum UNIGE_Status {UNIGE_RUNNING, UNIGE_FAILURE, UNIGE_SUCCESS, UNIGE_ERROR};

UNIGE_Status SS_to_Unige(CommYARP_BT::TickResult result)
{
	switch(result)
	{
		case CommYARP_BT::TickResult::Success:
		{
			return UNIGE_SUCCESS;
		} break;

		case CommYARP_BT::TickResult::Failure:
		{
			return UNIGE_FAILURE;
		} break;

		case CommYARP_BT::TickResult::Running:
		{
			return UNIGE_RUNNING;
		} break;

		case CommYARP_BT::TickResult::Error:
		{
			return UNIGE_ERROR;
		} break;

	}
};

int ExecuteSkill(const char *name)
{
    printf ("\n\n--------------\nTicking the skill: %s \n", name);

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

	std::cout  << "got answer " << answer.getResult().to_string() <<  " status " << status << std::endl;
#ifdef USE_BTCPP
	COMP->nodeMap[name]->setStatus( (BT::NodeStatus) SS_to_Unige(answer.getResult()));
#endif

	return SS_to_Unige(answer.getResult());
}

void ResetSkill(const char *name)
{
    printf("DUMMY Halting the skill: %s \n", name);
#ifdef USE_BTCPP
    printf("Set status to IDLE for Groot GUI\n");
	COMP->nodeMap[name]->setStatus( (BT::NodeStatus) SS_to_Unige(answer.getResult()));
	fflush(stdout);
#endif

	return;
}
