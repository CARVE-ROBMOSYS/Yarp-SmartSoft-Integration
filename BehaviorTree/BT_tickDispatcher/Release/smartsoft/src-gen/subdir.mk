################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src-gen/ActivityCore.cc \
../smartsoft/src-gen/BT_Tick_Query_HandlerCore.cc \
../smartsoft/src-gen/BT_tickDispatcher.cc \
../smartsoft/src-gen/BT_tickDispatcherImpl.cc \
../smartsoft/src-gen/main.cc 

CC_DEPS += \
./smartsoft/src-gen/ActivityCore.d \
./smartsoft/src-gen/BT_Tick_Query_HandlerCore.d \
./smartsoft/src-gen/BT_tickDispatcher.d \
./smartsoft/src-gen/BT_tickDispatcherImpl.d \
./smartsoft/src-gen/main.d 

OBJS += \
./smartsoft/src-gen/ActivityCore.o \
./smartsoft/src-gen/BT_Tick_Query_HandlerCore.o \
./smartsoft/src-gen/BT_tickDispatcher.o \
./smartsoft/src-gen/BT_tickDispatcherImpl.o \
./smartsoft/src-gen/main.o 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src-gen/%.o: ../smartsoft/src-gen/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/usr/local/" -I"/home/icub/SOFTWARE/smartsoft_3.6/include" -I"/home/icub/SOFTWARE/smartsoft_3.6/include/SmartSoft_CD_API" -I"/home/icub/SOFTWARE/smartsoft_3.6/include/AceSmartSoftKernel" -I"/home/icub/SOFTWARE/smartsoft_3.6/Yarp-SmartSoft-Integration/BehaviorTree/BT_tickDispatcher/smartsoft/src" -I"/home/icub/SOFTWARE/smartsoft_3.6/Yarp-SmartSoft-Integration/BehaviorTree/BT_tickDispatcher/smartsoft/src-gen" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


