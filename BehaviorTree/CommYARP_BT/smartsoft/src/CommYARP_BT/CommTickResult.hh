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
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#ifndef COMMYARP_BT_COMMTICKRESULT_H_
#define COMMYARP_BT_COMMTICKRESULT_H_

#include "CommYARP_BT/CommTickResultCore.hh"

namespace CommYARP_BT {
		
class CommTickResult : public CommTickResultCore {
	public:
		// default constructors
		CommTickResult();
		
		/**
		 * Constructor to set all values.
		 * NOTE that you have to keep this constructor consistent with the model!
		 * Use  at your own choice.
		 *
		 * The preferred way to set values for initialization is:
		 *      CommRepository::MyCommObject obj;
		 *      obj.setX(1).setY(2).setZ(3)...;
		 */
		// CommTickResult(const CommYARP_BT::TickResult &result);
		
		CommTickResult(const CommTickResultCore &commTickResult);
		CommTickResult(const DATATYPE &commTickResult);
		virtual ~CommTickResult();
		
		// use framework specific getter and setter methods from core (base) class
		using CommTickResultCore::get;
		using CommTickResultCore::set;
		
		//
		// feel free to add customized methods here
		//
};

inline std::ostream &operator<<(std::ostream &os, const CommTickResult &co)
{
	co.to_ostream(os);
	return os;
}
	
} /* namespace CommYARP_BT */
#endif /* COMMYARP_BT_COMMTICKRESULT_H_ */