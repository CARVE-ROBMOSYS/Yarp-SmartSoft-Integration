#include <iostream>
#include <yarp/os/Network.h>
#include <monitor.h>
#include <yarp/os/LogStream.h>

using namespace std;
using namespace yarp::os;

int main(int argc, char * argv[])
{
    Network yarp;
    Monitor module;
    ResourceFinder rf;
    rf.configure(argc, argv);

    if(!rf.setDefaultConfigFile("./config.ini")) //file in scenario-config-repo
    {
        yError() << "config.ini not found";
        return 1;
    }

    rf.setVerbose(true);
    cout << "Configuring and starting module. \n";

    module.runModule(rf);
    return 0;
}

