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
#include "SendTask.hh"
#include "SendClient.hh"

#include <iostream>

SendTask::SendTask(SmartACE::SmartComponent *comp) 
:	SendTaskCore(comp)
{
	std::cout << "constructor SendTask\n";
}
SendTask::~SendTask() 
{
	std::cout << "destructor SendTask\n";
}



int SendTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further

	// Get the server name to connect to, from the component parameters
	std::string serverPortName = COMP->getGlobalState().getSettings().getServerPort();

	// Connect to the server
	//
	// connect method can be called at any time, specifying source, destination and the protocol to use
	// The same conmmand can be used from terminal with:
	//
	// yarp connect /yarp/sendClient /yarp/sendServer tcp

	bool ret = yarp::os::Network::connect("/send_pattern/client", serverPortName, "tcp");
	return (!ret);
}

int SendTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	static int iteration = 0;

	std::cout << "Hello from SendTask. Iteration num " << iteration << std::endl;

	yarp::os::Bottle myData;							// instantiate a YARP portable data
	myData.addString("Hello from SendTask ");
	myData.addInt32(++iteration);
	myData.addDouble(3.14);

	// Send it to the destination module(s).
	// Data can be read from terminal by using the command `yarp read ... /yarp/sendClient`
    Smart::StatusCode status = COMP->yarpSendClient.send(myData);

    if (status == Smart::SMART_DISCONNECTED)
    {
        yError()<<"The client is not connected to nobody...";
    }
    else if(status == Smart::SMART_ERROR_COMMUNICATION)
    {
        yError()<<"Something is not working in the communication...";
    }
    else
    {
        yInfo()<<"The client correctly sent" << myData.toString();
    }

    // delay YARP style
    yarp::os::Time::delay(0.5);

    // it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int SendTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
