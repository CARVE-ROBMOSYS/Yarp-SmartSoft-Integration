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
#include "Test_QueryServerImpl.hh"

Test_QueryServerImpl::Test_QueryServerImpl(const std::string &componentName, int & argc, char ** argv)
:	SmartACE::SmartComponent(componentName, argc, argv)
{  }

Test_QueryServerImpl::Test_QueryServerImpl(const std::string &componentName, int & argc, char ** argv, const ACE_Sched_Params &sched_params)
:	SmartACE::SmartComponent(componentName, argc, argv, NULL, sched_params)
{  }

Test_QueryServerImpl::~Test_QueryServerImpl() 
{  }

Smart::StatusCode Test_QueryServerImpl::run(void)
{
	   Smart::StatusCode result = Smart::SMART_OK;

	   // open thread for managing all server-initiated-disconnects in this component
	   srvInitDiscHandler.start();

	   // if meanwile strg+c was called -> return immediatelly, without waiting on substate or reactor
	   if(!first_call_of_handle_signal) return Smart::SMART_ERROR;

	   componentIsRunning = true;

	   ///////////////////////////////////////////////////////////
	   //                                                       //
	   //  component is now fully initialized and running.      //
	   //  (untill the component is commanded to shutdown...)   //
	   //                                                       //
	   ///////////////////////////////////////////////////////////
	   if(getStateSlave() != NULL)
	   {
	      // block this thread till component is commanded to shut down...
	      getStateSlave()->acquire("shutdown");
	   } else {
	     // block this thread until component is commaned to shut down...
	     this->waitOnRuntimeCondVar();
	   }

	   return result;
}
void Test_QueryServerImpl::closeAllAssociatedTasks(const int &taskShutdownTimeLimit)
{
	if(this->getStateSlave() != NULL) {
		getStateSlave()->release("shutdown");
	}
	this->signalSmartTasksToStop(std::chrono::seconds(taskShutdownTimeLimit));
}
void Test_QueryServerImpl::cleanUpComponentResources()
{
	this->cleanUpInternalResources();
}