
#include <iostream>
#include "GoalTicker.h"

GoalTicker::GoalTicker(SmartACE::StateMaster *_stateMaster) : stateMaster(_stateMaster)
{

}

bool GoalTicker::configure(std::string target)
{
	if(!stateMaster)
		return false;
/*
	targetSkill = target;

	// I could check if associated status for this ticker actually exists in the slave component.
	// For now just list them all
	this->stateMaster->getAllMainStates(mainstates, target);
	for( auto ptr = mainstates.begin() ; ptr != mainstates.end(); ptr++ )
	{
		std::cout << (*ptr) << std::endl;
	}
*/
	return true;
}


CommYARP_BT::TickResult GoalTicker::tick(CommYARP_BT::TickCommand cmd, std::string params)
{
/*
	std::cout << "GoalTicker: ticking skill <" << targetSkill << "> state <" << params << "> " << std::endl;

	this->stateMaster->setWaitState(params, targetSkill); // throw();

	std::string feedback;
	this->stateMaster->getCurrentMainState(feedback, targetSkill);
	std::cout << "GoalTicker: feedback <" << feedback << ">" << std::endl;

	COMP->paramMaster->sendParameterWait(lispParamToParameterRequest("COMMNAVIGATIONOBJECTS.PLANNERPARAMS.DELETEGOAL"), response, "SmartPlannerBreadthFirstSearch", "param");

	std::cout << "Next Goal in mm (x)(y):";
	std::cin >> inString;
	str = "COMMNAVIGATIONOBJECTS.PLANNERPARAMS.SETDESTINATIONCIRCLE";
	str.append(inString);
	str.append("(100)");
	COMP->paramMaster->sendParameterWait(lispParamToParameterRequest(str), response, "SmartPlannerBreadthFirstSearch", "param");

*/
	return CommYARP_BT::TickResult::Running;
}
