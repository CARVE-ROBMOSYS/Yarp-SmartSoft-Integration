# Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

project(example_push_pattern)

add_executable(pushClient client.cpp)
add_executable(pushServer server.cpp)
target_link_libraries(pushClient ${YARP_LIBRARIES} YARP::YARP_smartsoft)
target_link_libraries(pushServer ${YARP_LIBRARIES} YARP::YARP_smartsoft)
