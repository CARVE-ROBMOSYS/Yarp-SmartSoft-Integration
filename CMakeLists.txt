# Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.


cmake_minimum_required(VERSION 3.5)

if(NOT ${CMAKE_VERSION} VERSION_LESS 3.8)
  cmake_policy(SET CMP0067 NEW)
endif()

# RPATH cmake policy set to NEW
if(NOT ${CMAKE_VERSION} VERSION_LESS 3.9)
  cmake_policy(SET CMP0068 NEW)
endif()

# Run automoc on generated files
if(NOT ${CMAKE_VERSION} VERSION_LESS 3.10)
  cmake_policy(SET CMP0071 NEW)
endif()

project(Yarp-SmartSoft-Integration
        VERSION 0.0.1
        LANGUAGES C CXX)
set(PROJECT_DESCRIPTION "Libraries and tools for Yarp-smartsoft integration")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Find YARP.  Point the YARP_DIR environment variable at your build.
find_package(YARP 3.0.0 REQUIRED)
find_package(AceSmartSoft REQUIRED)
find_package(Doxygen)

message(STATUS "Using:")
message(STATUS "  CMake: ${CMAKE_VERSION} (${CMAKE_COMMAND})")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} (${CMAKE_C_COMPILER})")
message(STATUS "  CXX Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} (${CMAKE_CXX_COMPILER})")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

include(YarpDoc)

add_subdirectory(integration)

option(COMPILE_examples "Compile examples" OFF)

