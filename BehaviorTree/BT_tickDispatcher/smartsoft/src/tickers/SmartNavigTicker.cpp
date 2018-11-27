
#include <iostream>
#include "BT_tickDispatcher.hh"

#include "SmartNavigTicker.h"

SmartNavigationTicker::SmartNavigationTicker()
{
	std::cout << "Smart Navig ticker:: constructor " << std::endl;
}

bool SmartNavigationTicker::configure(std::string target)
{

    yarp::os::Property        navigClientCfg;
    navigClientCfg.put("device", "navigation2DClient");
    navigClientCfg.put("local", "/robotPathPlannerExample");
    navigClientCfg.put("navigation_server", "/navigationServer");
    navigClientCfg.put("map_locations_server", "/mapServer");
    navigClientCfg.put("localization_server", "/localizationServer");

	//
	// Open navigation client
	//
	if(!navClient.open(navigClientCfg))
	{
		std::string errorStr = " Failed opening the navigation client, is the server running?";
		navClient.close();
		throw std::invalid_argument(errorStr);
	}


	navClient.view(iNav);
	if(iNav == nullptr)
	{
		std::string errorStr = "Cannot get navigation interface from navigation client";
		navClient.close();
		throw std::invalid_argument(errorStr);
	}

	yInfo() << "Navigation client successfully initialized";

	return true;
}


CommYARP_BT::TickResult SmartNavigationTicker::tick(CommYARP_BT::TickCommand cmd, std::string params)
{

	/*  USING QUERY PATTERN TO OTHER COMPONENT

	CommYARP_BT::CommTickCommand request;
	CommYARP_BT::CommTickResult  answer;

	request.setCommand(cmd);
	request.setParameter(params);

	std::cout << "tick " << __LINE__ <<  cmd << " " << params << std::endl;
	Smart::StatusCode status = COMP->bT_Navig_tick->query(request, answer);		// looks like the query function does not actually block
	std::cout << "tick " << __LINE__  <<  "  " << COMP->bT_Navig_tick << std::endl;


	// using query request + answer
	SmartACE::QueryId  id;
	Smart::StatusCode status = COMP->bT_Navig_tick->queryRequest(request, id);
	std::cout << status << " tick " << __LINE__  << "  " <<  COMP->bT_Navig_tick << std::endl;

	int trials = 0;
	status = Smart::SMART_NODATA;
	while(status != Smart::SMART_OK)
	{
		std::cout << "tick " << __LINE__  << "  " <<  COMP->bT_Navig_tick << std::endl;
		status = COMP->bT_Navig_tick->queryReceive(id, answer);
		std::cout << "tick " << __LINE__  << std::endl;
		usleep(300 *1000);
		std::cout << " Trying to get answer:  status " << status << " answer " << answer.getResult().to_string() << std::endl;
		if(trials >= 5)
			break;
		trials++;
		std::cout << "tick " << __LINE__  << std::endl;
	}
	std::cout << "SmartNavigationTicker: answer is  " << answer << "  with return status " << status << std::endl;

*/



	/*  USING NAVIGATION CLIENT IN HERE !!! */
	CommYARP_BT::TickResult result = CommYARP_BT::TickResult::Failure;
	yarp::dev::NavigationStatusEnum status = yarp::dev::navigation_status_error;

	// implement your query handling logic here and fill in the answer object
	static bool has_goal = false;

	std::cout << "Received request " << cmd << "  --  " << params << std::endl;
	std::cout << "has goal " << has_goal << std::endl;



	if(cmd == CommYARP_BT::TickCommand::Tick)
	{
		if(has_goal)
		{
			iNav->getNavigationStatus(status);
			std::cout << " navigation status " << yarp::os::Vocab::decode(status) << std::endl;

			switch(status)
			{
				case yarp::dev::navigation_status_goal_reached:
				case yarp::dev::navigation_status_idle:
					result = CommYARP_BT::TickResult::Success;
					has_goal = false;
					break;

				case yarp::dev::navigation_status_error:
				case yarp::dev::navigation_status_failing:
					result = CommYARP_BT::TickResult::Failure;
					has_goal = false;
					break;

				default:
					result = CommYARP_BT::TickResult::Running;
			}

		}
		else
		{
			if( iNav->gotoTargetByLocationName(params))   // this may require some time (???)
			{
				result = CommYARP_BT::TickResult::Running;
				has_goal = true;
			}
		}
	}

	if(cmd == CommYARP_BT::TickCommand::Halt)
	{
		iNav->stopNavigation();
		has_goal = false;
		result = CommYARP_BT::TickResult::Success;
	}

	std::cout << "SmartNavigationTicker: result is  " << result <<  std::endl;

	return result;
}
