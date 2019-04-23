
#include <iostream>
#include "RelayTicker.h"
#include <BT_tickDispatcher.hh>

using namespace CommYARP_BT;

RelayTicker::RelayTicker(tickClient *client) : _client(client)
{
}

bool RelayTicker::configure(std::string target)
{
	toMonitor_port.open(COMP->getGlobalState().getSettings().getTickManager_localPort() + "/" + target + "/monitor:o");
	targetSkill = target;
	return true;
}


CommYARP_BT::TickResult RelayTicker::tick(CommYARP_BT::TickCommand cmd, std::string params, std::string skillName)
{
	CommYARP_BT::CommTickCommand request;
	CommYARP_BT::CommTickResult  answer;

	request.setCommand(cmd);
	request.setParameter(params);

	std::cout << "Relay ticker - Got request: " << request.getCommand() << " " << request.getParameter()  << " skill " << skillName << std::endl;

	if(cmd == CommYARP_BT::TickCommand::Tick)
	{
		// send signal to the monitor
		BTMonitorMsg msg;
		msg.skill     = skillName;
		msg.event     = "e_from_bt";
		toMonitor_port.write(msg);
	}
	Smart::StatusCode status;
	status = _client->query(request, answer);

	// send signal to the monitor
	if(cmd == CommYARP_BT::TickCommand::Tick)
	{
		BTMonitorMsg msg;
		msg.skill     = skillName;
		msg.event     = "e_to_bt";
		toMonitor_port.write(msg);
	}
	std::cout << "Relay Ticker - Got answer:  " << answer << "  with return status " << status << std::endl;

	return answer.getResult();
}
