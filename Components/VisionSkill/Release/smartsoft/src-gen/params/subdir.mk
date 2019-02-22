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
	g++ -I"/usr/local/src/robot/SmartSoft/include" -I"/usr/local/src/robot/SmartSoft/include/SmartSoft_CD_API" -I"/usr/local/src/robot/SmartSoft/include/AceSmartSoftKernel" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/Components/VisionSkill/smartsoft/src" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/Components/VisionSkill/smartsoft/src-gen" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


