################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src/BT_runnerCore.cc \
../smartsoft/src/CompHandler.cc \
../smartsoft/src/ParameterStateStruct.cc \
../smartsoft/src/SmartStateChangeHandler.cc \
../smartsoft/src/Task1.cc 

CPP_SRCS += \
../smartsoft/src/ExecSkill_wrap.cpp 

CC_DEPS += \
./smartsoft/src/BT_runnerCore.d \
./smartsoft/src/CompHandler.d \
./smartsoft/src/ParameterStateStruct.d \
./smartsoft/src/SmartStateChangeHandler.d \
./smartsoft/src/Task1.d 

OBJS += \
./smartsoft/src/BT_runnerCore.o \
./smartsoft/src/CompHandler.o \
./smartsoft/src/ExecSkill_wrap.o \
./smartsoft/src/ParameterStateStruct.o \
./smartsoft/src/SmartStateChangeHandler.o \
./smartsoft/src/Task1.o 

CPP_DEPS += \
./smartsoft/src/ExecSkill_wrap.d 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src/%.o: ../smartsoft/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/usr/local/src/robot/SmartSoft/include" -I"/usr/local/src/robot/SmartSoft/include/SmartSoft_CD_API" -I"/usr/local/src/robot/SmartSoft/include/AceSmartSoftKernel" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/BehaviorTree/BT_runner/smartsoft/src" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/BehaviorTree/BT_runner/smartsoft/src-gen" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

smartsoft/src/%.o: ../smartsoft/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/usr/local/src/robot/SmartSoft/include" -I"/usr/local/src/robot/SmartSoft/include/SmartSoft_CD_API" -I"/usr/local/src/robot/SmartSoft/include/AceSmartSoftKernel" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/BehaviorTree/BT_runner/smartsoft/src" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/BehaviorTree/BT_runner/smartsoft/src-gen" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


