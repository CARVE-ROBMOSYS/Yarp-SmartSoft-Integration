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
#include "Test_DummySendPattern_Client.hh"
	
	
Test_DummySendPattern_Client Test_DummySendPattern_Client::_test_DummySendPattern_Client;
	
int main(int argc, char *argv[])
{
	std::cout << "main...\n";
	Test_DummySendPattern_Client::instance()->init(argc, argv);
	Test_DummySendPattern_Client::instance()->run();
	std::cout << "... main() end. return 0." << std::endl;
	return 0;
}
