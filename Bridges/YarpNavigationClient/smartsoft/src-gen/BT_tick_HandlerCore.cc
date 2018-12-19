//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#include "BT_tick_HandlerCore.hh"
#include "BT_tick_Handler.hh"

// include observers

BT_tick_HandlerCore::BT_tick_HandlerCore(Smart::IQueryServerPattern<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult, SmartACE::QueryId>* server)
:	Smart::IQueryServerHandler<CommYARP_BT::CommTickCommand, CommYARP_BT::CommTickResult, SmartACE::QueryId>(server)
{
	
}

BT_tick_HandlerCore::~BT_tick_HandlerCore()
{
	
}

void BT_tick_HandlerCore::updateAllCommObjects()
{
}

void BT_tick_HandlerCore::notify_all_interaction_observers() {
	std::unique_lock<std::mutex> lock(interaction_observers_mutex);
	// try dynamically down-casting this class to the derived class 
	// (we can do it safely here as we exactly know the derived class)
	if(const BT_tick_Handler* bT_tick_Handler = dynamic_cast<const BT_tick_Handler*>(this)) {
		for(auto it=interaction_observers.begin(); it!=interaction_observers.end(); it++) {
			(*it)->on_update_from(bT_tick_Handler);
		}
	}
}

void BT_tick_HandlerCore::attach_interaction_observer(BT_tick_HandlerObserverInterface *observer) {
	std::unique_lock<std::mutex> lock(interaction_observers_mutex);
	interaction_observers.push_back(observer);
}

void BT_tick_HandlerCore::detach_interaction_observer(BT_tick_HandlerObserverInterface *observer) {
	std::unique_lock<std::mutex> lock(interaction_observers_mutex);
	interaction_observers.remove(observer);
}
