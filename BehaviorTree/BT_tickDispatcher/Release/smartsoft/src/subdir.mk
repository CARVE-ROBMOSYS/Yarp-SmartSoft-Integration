################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src/Activity.cc \
../smartsoft/src/BT_Tick_Query_Handler.cc \
../smartsoft/src/BT_tickDispatcherCore.cc \
../smartsoft/src/CompHandler.cc \
../smartsoft/src/ParameterStateStruct.cc \
../smartsoft/src/SmartStateChangeHandler.cc \
../smartsoft/src/TriggerHandler.cc 

CC_DEPS += \
./smartsoft/src/Activity.d \
./smartsoft/src/BT_Tick_Query_Handler.d \
./smartsoft/src/BT_tickDispatcherCore.d \
./smartsoft/src/CompHandler.d \
./smartsoft/src/ParameterStateStruct.d \
./smartsoft/src/SmartStateChangeHandler.d \
./smartsoft/src/TriggerHandler.d 

OBJS += \
./smartsoft/src/Activity.o \
./smartsoft/src/BT_Tick_Query_Handler.o \
./smartsoft/src/BT_tickDispatcherCore.o \
./smartsoft/src/CompHandler.o \
./smartsoft/src/ParameterStateStruct.o \
./smartsoft/src/SmartStateChangeHandler.o \
./smartsoft/src/TriggerHandler.o 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src/%.o: ../smartsoft/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/usr/local/src/robot/SmartSoft/include" -I"/usr/local/src/robot/SmartSoft/include/SmartSoft_CD_API" -I"/usr/local/src/robot/SmartSoft/include/AceSmartSoftKernel" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/BehaviorTree/BT_tickDispatcher/smartsoft/src" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/BehaviorTree/BT_tickDispatcher/smartsoft/src-gen" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


