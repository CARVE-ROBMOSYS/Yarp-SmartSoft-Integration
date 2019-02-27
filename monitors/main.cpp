#include <iostream>
#include <yarp/os/Network.h>
#include <monitor.h>
using namespace std;
using namespace yarp::os;

int main(int argc, char * argv[])
{
    Network yarp;
    Monitor module;
    ResourceFinder rf;
    rf.setDefaultConfigFile("config.ini"); //file in scenario-config-repo
    rf.setVerbose(true);

    cout << "Configuring and starting module. \n";
    module.runModule(rf);   // This calls configure(rf) and, upon success, the module execution begins with a call to updateModule()
    cout<<"Main returning..."<<endl;
    return 0;
}

