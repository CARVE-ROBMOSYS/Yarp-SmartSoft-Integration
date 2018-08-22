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

int ExecuteOrResetSkill(const char *name, int is_tick)
{
  if (is_tick == 1) {
    printf ("Ticking the skill: %s \n", name);
  } else {
    printf ("Halting the skill: %s \n", name);
    return SUCCESS;
  }

  if (strcmp(name,"Action1SecondSuccess") == 0) {
    int return_status = DoDummySkill(SUCCESS, 1000);
    printf ("I am returning %d \n", return_status);

    return return_status;
  }
  else if (strcmp(name,"ActionRunning") == 0) {
    int return_status = DoDummySkill(RUNNING, 1);
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
  else {
    printf ("Node %s not known \n", name);
    return ERROR;
  }

}

int ExecuteSkill(const char *name)
{
//	int ret = ExecuteOrResetSkill(name,1);				// ToBeRemoved

	CommYARP_BT::CommTickCommand request;
	CommYARP_BT::CommTickResult  answer;
	request.setCommand(CommYARP_BT::TickCommand::Tick);
	request.setParameter(name);

//	Smart::StatusCode status = COMP->tickRequest->query(request, answer);		// looks like the query function does not actually block

	// using query request + answer
	SmartACE::QueryId  id;
	Smart::StatusCode status = COMP->tickRequest->queryRequest(request, id);
	std::cout << "ExecuteSkill: Ticking skill " << name << " ... queryRequest return status is " << status << std::endl;

	status = Smart::SMART_NODATA;
	while(status != Smart::SMART_OK)
	{
		status = COMP->tickRequest->queryReceive(id, answer);
		sleep(0.3);
//		std::cout << " Trying to get answer:  status " << status << " answer " << answer.getResult().to_string() << std::endl;
		if(status == Smart::SMART_OK)
			break;
	}

	std::cout  << "got answer " << answer.getResult().to_string() <<  " status " << status << std::endl << std::endl;
//	sleep(10);

	return answer.getResult();
}

void ResetSkill(const char *name)
{
	ExecuteOrResetSkill(name,0);
	return;
}
