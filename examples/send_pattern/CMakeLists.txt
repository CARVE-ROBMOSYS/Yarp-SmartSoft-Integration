project(example_send_pattern)

add_executable(sendClient client.cpp)
add_executable(sendServer server.cpp)
target_link_libraries(sendClient ${YARP_LIBRARIES} YARP::YARP_smartsoft)
target_link_libraries(sendServer ${YARP_LIBRARIES} YARP::YARP_smartsoft)
