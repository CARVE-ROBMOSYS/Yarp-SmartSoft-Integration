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
#ifndef _BT_TICK_QUERY_HANDLER_OBSERVER_INTERFACE_HH
#define _BT_TICK_QUERY_HANDLER_OBSERVER_INTERFACE_HH

// forward declaration
class BT_Tick_Query_Handler;

class BT_Tick_Query_HandlerObserverInterface {
public:
	virtual ~BT_Tick_Query_HandlerObserverInterface() {  }

	virtual void on_update_from(const BT_Tick_Query_Handler *subject) = 0;
};

#endif
