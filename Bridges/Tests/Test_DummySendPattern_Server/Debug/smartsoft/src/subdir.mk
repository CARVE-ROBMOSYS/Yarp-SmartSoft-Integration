################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src/CompHandler.cc \
../smartsoft/src/ParameterStateStruct.cc \
../smartsoft/src/SmartStateChangeHandler.cc \
../smartsoft/src/Test_DummySendPattern_ServerCore.cc 

CC_DEPS += \
./smartsoft/src/CompHandler.d \
./smartsoft/src/ParameterStateStruct.d \
./smartsoft/src/SmartStateChangeHandler.d \
./smartsoft/src/Test_DummySendPattern_ServerCore.d 

OBJS += \
./smartsoft/src/CompHandler.o \
./smartsoft/src/ParameterStateStruct.o \
./smartsoft/src/SmartStateChangeHandler.o \
./smartsoft/src/Test_DummySendPattern_ServerCore.o 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src/%.o: ../smartsoft/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


