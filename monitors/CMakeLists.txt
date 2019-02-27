project(carveMonitors)
cmake_minimum_required(VERSION 2.8)



find_package(YARP)
find_package(rFSM REQUIRED)

include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(MONITOR_SOURCES

${CMAKE_CURRENT_SOURCE_DIR}/src/monitor.cpp

)



add_executable(example_monitor main.cpp ${MONITOR_SOURCES})
target_link_libraries(example_monitor ${YARP_LIBRARIES} rFSMTools::rFSM)


