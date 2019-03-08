
#include <iostream>
#include "RelayTicker.h"

using namespace CommYARP_BT;

RelayTicker::RelayTicker(tickClient *client) : _client(client)
{

}

bool RelayTicker::configure(std::string target)
{

	return true;
}


CommYARP_BT::TickResult RelayTicker::tick(CommYARP_BT::TickCommand cmd, std::string params)
{
	CommYARP_BT::CommTickCommand request;
	CommYARP_BT::CommTickResult  answer;

	request.setCommand(cmd);
	request.setParameter(params);

	std::cout << "Relay ticker - Got request: " << request.getCommand() << " " << request.getParameter()  << std::endl;

	Smart::StatusCode status;
	status = _client->query(request, answer);

/*
	// using query request + answer
	SmartACE::QueryId  id;
	status = _client->queryRequest(request, id);
	std::cout << status << " tick " << __LINE__  << std::endl;

	int trials = 0;
	status = Smart::SMART_NODATA;
	while(status != Smart::SMART_OK)
	{
		std::cout << "tick " << __LINE__  << std::endl;
		status = _client->queryReceive(id, answer);
		std::cout << "tick " << __LINE__  << std::endl;
		usleep(300 *1000);
		std::cout << " Trying to get answer [id"<< id << "] :  status " << status << " answer " << answer.getResult().to_string() << std::endl;
		if(trials >= 20)
			break;
		trials++;
		std::cout << "tick " << __LINE__  << std::endl;
	}
	std::cout << "SmartNavigationTicker[id"<< id << "]  answer is  " << answer << "  with return status " << status << std::endl;
*/

	std::cout << "Relay Ticker - Got answer:  " << answer << "  with return status " << status << std::endl;

	return answer.getResult();
//	return TickResult::Running;
}
