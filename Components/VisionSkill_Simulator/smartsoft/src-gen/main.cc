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
#include "VisionSkill_Simulator.hh"
	
	
VisionSkill_Simulator VisionSkill_Simulator::_visionSkill_Simulator;
	
int main(int argc, char *argv[])
{
	std::cout << "main...\n";
	VisionSkill_Simulator::instance()->init(argc, argv);
	VisionSkill_Simulator::instance()->run();
	std::cout << "... main() end. return 0." << std::endl;
	return 0;
}