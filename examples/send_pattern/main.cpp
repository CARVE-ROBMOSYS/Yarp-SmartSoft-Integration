#include <yarp/smartsoft/SendPatternClient.h>

int main()
{
    yarp::os::Network yarp;
    yarp::smartsoft::SendPatternClient<yarp::os::Bottle> spc("/send_pattern/client");

    return 0;
}
