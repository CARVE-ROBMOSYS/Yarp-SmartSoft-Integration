# Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

project(example_send_pattern)

add_executable(sendClient client.cpp)
add_executable(sendServer server.cpp)
target_link_libraries(sendClient ${YARP_LIBRARIES} YARP::YARP_smartsoft)
target_link_libraries(sendServer ${YARP_LIBRARIES} YARP::YARP_smartsoft)
