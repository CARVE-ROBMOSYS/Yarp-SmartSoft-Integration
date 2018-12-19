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
#ifndef COMMYARP_BT_COMMTICKCOMMAND_ACE_H_
#define COMMYARP_BT_COMMTICKCOMMAND_ACE_H_

#include "CommYARP_BT/CommTickCommand.hh"

#include <ace/CDR_Stream.h>

// serialization operator for DataStructure CommTickCommand
ACE_CDR::Boolean operator<<(ACE_OutputCDR &cdr, const CommYARP_BTIDL::CommTickCommand &data);

// de-serialization operator for DataStructure CommTickCommand
ACE_CDR::Boolean operator>>(ACE_InputCDR &cdr, CommYARP_BTIDL::CommTickCommand &data);

// serialization operator for CommunicationObject CommTickCommand
ACE_CDR::Boolean operator<<(ACE_OutputCDR &cdr, const CommYARP_BT::CommTickCommand &obj);

// de-serialization operator for CommunicationObject CommTickCommand
ACE_CDR::Boolean operator>>(ACE_InputCDR &cdr, CommYARP_BT::CommTickCommand &obj);

#endif /* COMMYARP_BT_COMMTICKCOMMAND_ACE_H_ */