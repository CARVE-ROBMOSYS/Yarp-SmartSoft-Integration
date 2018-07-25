#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "ExecSkill_wrap.h"
#include "BT_engine.hh"
#include "CommYARP_BT/CommTickCommand.hh"

int ExecuteSkill(const char *name)
{
	CommYARP_BT::CommTickCommand request;
	CommYARP_BT::CommTickResult  answer;
	request.setCommand(CommYARP_BT::TickCommand::Tick);
	request.setParameter(name);
	COMP->tickRequest->query(request, answer);

	return answer.getResult();
}

