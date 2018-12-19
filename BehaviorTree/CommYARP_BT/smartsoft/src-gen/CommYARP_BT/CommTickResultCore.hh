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
#ifndef COMMYARP_BT_COMMTICKRESULT_CORE_H_
#define COMMYARP_BT_COMMTICKRESULT_CORE_H_

#include "CommYARP_BT/CommTickResultData.hh"
#include "CommYARP_BT/enumTickResult.hh"

#include <iostream>
#include <string>
#include <list>

namespace CommYARP_BT {
	
class CommTickResultCore {
protected:
	// data structure
	CommYARP_BTIDL::CommTickResult idl_CommTickResult;
	
public:
	// give a publicly accessible type-name for the template parameter IDL
	typedef CommYARP_BTIDL::CommTickResult DATATYPE;
	
	#ifdef ENABLE_HASH
		static size_t generateDataHash(const DATATYPE &);
	#endif
	
	static const char* getCompiledHash();
	static void getAllHashValues(std::list<std::string> &hashes);
	static void checkAllHashValues(std::list<std::string> &hashes);
	
	// default constructors
	CommTickResultCore();
	CommTickResultCore(const DATATYPE &data);
	// default destructor
	virtual ~CommTickResultCore();
	
	const DATATYPE& get() const { return idl_CommTickResult; }
	operator const DATATYPE&() const { return idl_CommTickResult; }
	DATATYPE& set() { return idl_CommTickResult; }

	static inline std::string identifier(void) { return "CommYARP_BT::CommTickResult"; }
	
	// helper method to easily implement output stream in derived classes
	void to_ostream(std::ostream &os = std::cout) const;
	
	// convert to xml stream
	void to_xml(std::ostream &os, const std::string &indent = "") const;
	
	// restore from xml stream
	void from_xml(std::istream &is);
	
	// User Interface
	
	// getter and setter for element Result
	inline CommYARP_BT::TickResult getResult() const { return CommYARP_BT::TickResult(idl_CommTickResult.result); }
	inline CommTickResultCore& setResult(const CommYARP_BT::TickResult &result) { idl_CommTickResult.result = result; return *this; }
};

} /* namespace CommYARP_BT */
#endif /* COMMYARP_BT_COMMTICKRESULT_CORE_H_ */