
project(comm_patterns)

set(comm_patterns_HDRS include/send_pattern/SendPatternClient.h
                       include/send_pattern/SendPatternServer.h)

set(comm_patterns_SRCS src/send_pattern/SendPatternClient.cpp
                       src/send_pattern/SendPatternServer.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
             PREFIX "Source Files"
             FILES ${comm_patterns_SRCS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
             PREFIX "Header Files"
             FILES ${comm_patterns_HDRS})

add_library(comm_patterns SHARED ${comm_patterns_SRCS} ${comm_patterns_HDRS})

target_include_directories(comm_patterns PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                                $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(comm_patterns PUBLIC YARP::YARP_conf
                                           YARP::YARP_OS)

if(CMAKE_VERSION VERSION_LESS 3.8)
  target_compile_features(comm_patterns PUBLIC cxx_auto_type
                                               cxx_constexpr
                                               cxx_defaulted_move_initializers
                                               cxx_deleted_functions
                                               cxx_extern_templates
                                               cxx_final
                                               cxx_nullptr
                                               cxx_override)
else()
  target_compile_features(comm_patterns PUBLIC cxx_std_11)
endif()

install(TARGETS comm_patterns
        EXPORT comm_patterns
        COMPONENT runtime
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/comm_patterns)


set_property(TARGET comm_patterns PROPERTY PUBLIC_HEADER ${comm_patterns_HDRS})

