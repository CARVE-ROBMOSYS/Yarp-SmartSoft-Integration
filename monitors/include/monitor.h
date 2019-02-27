#ifndef MONITOR_H
#define MONITOR_H

#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/BufferedPort.h>
#include <rfsm.h>
using namespace std;
using namespace yarp::os;

class Monitor : public RFModule
{
public:
    Monitor();
//    void set_filename(std::string rfsm_filename);
    bool configure(yarp::os::ResourceFinder &rf);

private:
    double getPeriod();
    bool updateModule();
    bool respond(const Bottle& command, Bottle& reply);
    bool interruptModule();
    bool close();
    BufferedPort<Bottle>  event_port_; // a port to handle event messages
    Port state_port_; // a port to rpc requests

    rfsm::StateMachine rfsm;





};

#endif // MONITOR_H
