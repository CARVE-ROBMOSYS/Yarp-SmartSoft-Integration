
#include <iostream>
#include "SmartTicker.h"

SmartTicker::SmartTicker(SmartACE::StateMaster *_stateMaster) : stateMaster(_stateMaster)
{

}

bool SmartTicker::configure(std::string target)
{
	if(!stateMaster)
		return false;

	targets = target;
}


ITickable::tickResult SmartTicker::tick(tickCommand cmd, std::string params)
{
	Smart::StatusCode retStatus;
	std::string targetState("running");
	std::string targetSkill = targets;		// TDR useless!!

	this->stateMaster->getAllMainStates(mainstates, targetSkill);
	for( auto ptr = mainstates.begin() ; ptr != mainstates.end(); ptr++ )
	{
		std::cout << (*ptr) << std::endl;
	}

	std::cout << "SmartTicker: ticking skill " << targetSkill << " state " << targetState << std::endl;
	this->stateMaster->setWaitState(targetState, targetSkill); // throw();
}
