#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "ExecSkill_wrap.h"
#include "BT_engine.hh"
#include "CommYARP_BT/CommTickCommand.hh"

// Dummy execution for testing purpose only, to be removed
int DoDummySkill(int status, int elapsed_time_milliseconds)
{
    sleep(elapsed_time_milliseconds/1000);
    return status;
}

int DummyExecution(const char *name)
{
	if (strcmp(name,"Action1SecondSuccess") == 0)
	{
		int return_status = DoDummySkill(SUCCESS, 1000);
		printf ("I am returning %d \n", return_status);

		return return_status;
	}
	else if (strcmp(name, "Action1SecondFailure") == 0) {

		int return_status = DoDummySkill(FAILURE, 1000);
		printf ("I am returning %d \n", return_status);

		return return_status;

	}
	else if (strcmp(name, "ConditionTrue") == 0) {

		int return_status = DoDummySkill(SUCCESS, 0);
		printf ("I am returning %d \n", return_status);

		return return_status;
	}
	else if (strcmp(name, "ConditionFalse") == 0) {

		int return_status = DoDummySkill(FAILURE, 0);
		printf ("I am returning %d \n", return_status);

		return return_status;
	}
	else
	{
		printf ("Node %s not known \n", name);
		return ERROR;
	}
}

int ExecuteSkill(const char *name)
{
	printf("Executing skill %s\n", name);
//	return DummyExecution(name);				// ToBeRemoved

	CommYARP_BT::CommTickCommand request;
	CommYARP_BT::CommTickResult  answer;
	request.setCommand(CommYARP_BT::TickCommand::Tick);
	request.setParameter(name);
	COMP->tickRequest->query(request, answer);

	return answer.getResult();
}

