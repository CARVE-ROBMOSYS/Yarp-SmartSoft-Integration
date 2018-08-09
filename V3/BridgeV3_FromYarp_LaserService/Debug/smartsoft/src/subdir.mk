################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src/BridgeV3_FromYarp_LaserServiceCore.cc \
../smartsoft/src/CompHandler.cc \
../smartsoft/src/DummyTask.cc \
../smartsoft/src/ParameterStateStruct.cc \
../smartsoft/src/SmartStateChangeHandler.cc 

CC_DEPS += \
./smartsoft/src/BridgeV3_FromYarp_LaserServiceCore.d \
./smartsoft/src/CompHandler.d \
./smartsoft/src/DummyTask.d \
./smartsoft/src/ParameterStateStruct.d \
./smartsoft/src/SmartStateChangeHandler.d 

OBJS += \
./smartsoft/src/BridgeV3_FromYarp_LaserServiceCore.o \
./smartsoft/src/CompHandler.o \
./smartsoft/src/DummyTask.o \
./smartsoft/src/ParameterStateStruct.o \
./smartsoft/src/SmartStateChangeHandler.o 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src/%.o: ../smartsoft/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


