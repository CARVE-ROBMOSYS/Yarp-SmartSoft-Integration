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
#ifndef _TASK1_HH
#define _TASK1_HH

#include <memory>

#include "Task1Core.hh"
#include <caml/mlvalues.h>

#ifdef USE_BTCPP
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <behaviortree_cpp/loggers/bt_file_logger.h>
#include <behaviortree_cpp/loggers/bt_zmq_publisher.h>
#include <behaviortree_cpp/loggers/bt_minitrace_logger.h>
#endif

#include "tinyXML2/tinyxml2.h"

class Task1  : public Task1Core
{
private:
	value behaviourTree;

#ifdef USE_BTCPP
    std::shared_ptr<BT::StdCoutLogger>   logger_cout;
    std::shared_ptr<BT::MinitraceLogger> logger_minitrace;
    std::shared_ptr<BT::FileLogger>      logger_file;
    std::shared_ptr<BT::PublisherZMQ>    publisher_zmq;
#endif

public:
	Task1(SmartACE::SmartComponent *comp);
	virtual ~Task1();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();
};

#endif
