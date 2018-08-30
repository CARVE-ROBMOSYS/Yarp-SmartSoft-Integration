
#include <iostream>
#include "SmartTicker.h"

SmartTicker::SmartTicker(SmartACE::StateMaster *_stateMaster) : stateMaster(_stateMaster)
{

}

bool SmartTicker::configure(std::string target)
{
	if(!stateMaster)
		return false;

	targetSkill = target;

	// I could check if associated status for this ticker actually exists in the slave component.
	// For now just list them all
	this->stateMaster->getAllMainStates(mainstates, target);
	for( auto ptr = mainstates.begin() ; ptr != mainstates.end(); ptr++ )
	{
		std::cout << (*ptr) << std::endl;
	}

	return true;
}


CommYARP_BT::TickResult SmartTicker::tick(CommYARP_BT::TickCommand cmd, std::string params)
{
	std::cout << "SmartTicker: ticking skill <" << targetSkill << "> state <" << params << "> " << std::endl;

	this->stateMaster->setWaitState(params, targetSkill); // throw();

	std::string feedback;
	this->stateMaster->getCurrentMainState(feedback, targetSkill);
	std::cout << "SmartTicker: feedback <" << feedback << ">" << std::endl;

	return CommYARP_BT::TickResult::Running;
}
