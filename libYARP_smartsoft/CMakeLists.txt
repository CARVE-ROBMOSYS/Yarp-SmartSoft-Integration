
project(YARP_smartsoft)

set(YARP_smartsoft_HDRS include/yarp/smartsoft/PatternClientBase.h
                        include/yarp/smartsoft/QueryPatternClient.h
                        include/yarp/smartsoft/QueryPatternServer.h
                        include/yarp/smartsoft/SendPatternClient.h
                        include/yarp/smartsoft/SendPatternServer.h
                        include/yarp/smartsoft/SmartVocabs.h)

set(YARP_smartsoft_IMPL_HDRS )

set(YARP_smartsoft_SRCS src/PatternClientBase.cpp
                        src/SendPatternClient.cpp
                        src/SendPatternServer.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
             PREFIX "Source Files"
             FILES ${YARP_smartsoft_SRCS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
             PREFIX "Header Files"
             FILES ${YARP_smartsoft_HDRS})

add_library(YARP_smartsoft SHARED ${YARP_smartsoft_SRCS}
                                  ${YARP_smartsoft_HDRS}
                                  ${YARP_smartsoft_IMPL_HDRS})
add_library(YARP::YARP_smartsoft ALIAS YARP_smartsoft)

target_include_directories(YARP_smartsoft PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                                $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(YARP_smartsoft PUBLIC YARP::YARP_conf
                                            YARP::YARP_OS
                                            AceSmartSoftKernel)

if(CMAKE_VERSION VERSION_LESS 3.8)
  target_compile_features(YARP_smartsoft PUBLIC cxx_auto_type
                                                cxx_constexpr
                                                cxx_defaulted_move_initializers
                                                cxx_deleted_functions
                                                cxx_extern_templates
                                                cxx_final
                                                cxx_nullptr
                                                cxx_override)
else()
  target_compile_features(YARP_smartsoft PUBLIC cxx_std_11)
endif()

set_property(TARGET YARP_smartsoft PROPERTY PUBLIC_HEADER ${YARP_smartsoft_HDRS})
set_property(TARGET YARP_smartsoft PROPERTY PRIVATE_HEADER ${YARP_smartsoft_IMPL_HDRS})

install(TARGETS YARP_smartsoft
        EXPORT YARP
        COMPONENT runtime
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/yarp/smartsoft)


