################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src/CompHandler.cc \
../smartsoft/src/ParameterStateStruct.cc \
../smartsoft/src/SequencePathCore.cc \
../smartsoft/src/SequencerActivity.cc \
../smartsoft/src/SmartStateChangeHandler.cc \
../smartsoft/src/TickHandler.cc 

CC_DEPS += \
./smartsoft/src/CompHandler.d \
./smartsoft/src/ParameterStateStruct.d \
./smartsoft/src/SequencePathCore.d \
./smartsoft/src/SequencerActivity.d \
./smartsoft/src/SmartStateChangeHandler.d \
./smartsoft/src/TickHandler.d 

OBJS += \
./smartsoft/src/CompHandler.o \
./smartsoft/src/ParameterStateStruct.o \
./smartsoft/src/SequencePathCore.o \
./smartsoft/src/SequencerActivity.o \
./smartsoft/src/SmartStateChangeHandler.o \
./smartsoft/src/TickHandler.o 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src/%.o: ../smartsoft/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/usr/local/src/robot/SmartSoft/include" -I"/usr/local/src/robot/SmartSoft/include/SmartSoft_CD_API" -I"/usr/local/src/robot/SmartSoft/include/AceSmartSoftKernel" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/Components/SequencePath/smartsoft/src" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/Components/SequencePath/smartsoft/src-gen" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


