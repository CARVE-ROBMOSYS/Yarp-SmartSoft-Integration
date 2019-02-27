#include <monitor.h>
#include <iostream>
#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/LogStream.h>
using namespace std;
using namespace yarp::os;

double Monitor::getPeriod()
{
    return 1.0; // TODO change to 0.1
}

bool Monitor::updateModule()
{
    cout<<  "Current state : " << rfsm.getCurrentState() << endl;
    Bottle *input = event_port_.read(false);

    if (input!=NULL) {

        cout<< "event registered : " << input->toString().c_str() << endl;
        rfsm.sendEvent(input->toString());
        rfsm.step(1);
    }

    return true;
}

bool Monitor::respond(const Bottle &command, Bottle &reply)
{
    if (command.get(0).asString() == "state")
    {
        reply.addString(rfsm.getCurrentState());
        return true;
    }
    reply.addString("command not recognized");

    return true;
}


bool Monitor::configure(yarp::os::ResourceFinder &rf)
{
    std::string filename;
    if (rf.check("filename"))
    {
        filename = rf.find("filename").asString();
    }
    else
    {
        yError() << " Wrong filename";
        return false;

    }

    if (!event_port_.open("/monitor/"+filename+"/event:i"))
    {
             yError() << "Cannot open port " << "/monitor/" << filename << "/event:i";
        return false;
    }

    if(!state_port_.open("/monitor/"+filename+"/rpc:i"))
    {
        yError() << "Cannot open port " << "/monitor/" << filename << "/rpc:i";

        return false;
    }

    if(!attach(state_port_))
    {
        yError() << "Cannot attach to module the state port ";

        return false;
    }

    if(!rfsm.load(filename))
    {
        yError() << "Cannot load rFSM " << filename;
        return false;
    }
    return true;
}
// Interrupt function.
bool Monitor::interruptModule()
{
    cout << "Interrupting your module, for port cleanup" << endl;
    return true;
}
// Close function, to perform cleanup.
bool Monitor::close()
{
    // optional, close port explicitly
    cout << "Calling close function\n";
    event_port_.close();
    return true;
}
