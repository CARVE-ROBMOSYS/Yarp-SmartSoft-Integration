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
#include <iostream>
#include "Test_QueryServer.hh"
	
	
Test_QueryServer Test_QueryServer::_test_QueryServer;
	
int main(int argc, char *argv[])
{
	std::cout << "main...\n";
	Test_QueryServer::instance()->init(argc, argv);
	Test_QueryServer::instance()->run();
	std::cout << "... main() end. return 0." << std::endl;
	return 0;
}
