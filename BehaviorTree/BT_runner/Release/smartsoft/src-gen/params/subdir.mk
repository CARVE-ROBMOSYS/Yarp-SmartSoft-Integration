################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src-gen/params/ParameterUpdateHandler.cc 

CC_DEPS += \
./smartsoft/src-gen/params/ParameterUpdateHandler.d 

OBJS += \
./smartsoft/src-gen/params/ParameterUpdateHandler.o 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src-gen/params/%.o: ../smartsoft/src-gen/params/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/usr/local/" -I"/home/icub/SOFTWARE/smartsoft_3.6/include" -I"/home/icub/SOFTWARE/smartsoft_3.6/include/SmartSoft_CD_API" -I"/home/icub/SOFTWARE/smartsoft_3.6/include/AceSmartSoftKernel" -I"/home/icub/SOFTWARE/smartsoft_3.6/Yarp-SmartSoft-Integration/BehaviorTree/BT_runner/smartsoft/src" -I"/home/icub/SOFTWARE/smartsoft_3.6/Yarp-SmartSoft-Integration/BehaviorTree/BT_runner/smartsoft/src-gen" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


