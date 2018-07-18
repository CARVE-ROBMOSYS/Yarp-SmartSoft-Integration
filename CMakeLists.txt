# Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

project(Yarp-SmartSoft-Integration)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Find YARP.  Point the YARP_DIR environment variable at your build.
find_package(YARP REQUIRED)
find_package(AceSmartSoft REQUIRED)

add_subdirectory(libYARP_smartsoft)
