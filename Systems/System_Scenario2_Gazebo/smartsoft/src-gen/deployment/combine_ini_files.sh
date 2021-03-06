#!/bin/bash
#--------------------------------------------------------------------------
# Code generated by the SmartSoft MDSD Toolchain
# The SmartSoft Toolchain has been developed by:
#  
# Service Robotics Research Center
# University of Applied Sciences Ulm
# Prittwitzstr. 10
# 89075 Ulm (Germany)
#
# Information about the SmartSoft MDSD Toolchain is available at:
# www.servicerobotik-ulm.de
#
# Please do not modify this file. It will be re-generated
# running the code generator.
#--------------------------------------------------------------------------
#
# This script collects the generated ini-file parts and combines them into single ini-files (one for each component artefact)
#

# create ini-file BT_runner.ini
echo "create ini-file BT_runner.ini"
cp src-gen/system/BT_runner.ini src-gen/deployment/
cat src-gen/params/BT_runner.ini >> src-gen/deployment/BT_runner.ini

# create ini-file BT_tickDispatcher.ini
echo "create ini-file BT_tickDispatcher.ini"
cp src-gen/system/BT_tickDispatcher.ini src-gen/deployment/
cat src-gen/params/BT_tickDispatcher.ini >> src-gen/deployment/BT_tickDispatcher.ini

# create ini-file GenericMovementSkill.ini
echo "create ini-file GenericMovementSkill.ini"
cp src-gen/system/GenericMovementSkill.ini src-gen/deployment/
cat src-gen/params/GenericMovementSkill.ini >> src-gen/deployment/GenericMovementSkill.ini

# create ini-file YarpNavigationClient.ini
echo "create ini-file YarpNavigationClient.ini"
cp src-gen/system/YarpNavigationClient.ini src-gen/deployment/
cat src-gen/params/YarpNavigationClient.ini >> src-gen/deployment/YarpNavigationClient.ini

# create ini-file VisionSkill_Simulator.ini
echo "create ini-file VisionSkill_Simulator.ini"
cp src-gen/system/VisionSkill_Simulator.ini src-gen/deployment/
cat src-gen/params/VisionSkill_Simulator.ini >> src-gen/deployment/VisionSkill_Simulator.ini

