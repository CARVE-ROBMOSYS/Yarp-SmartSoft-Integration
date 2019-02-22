################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src-gen/TickHandlerCore.cc \
../smartsoft/src-gen/VisionSkill.cc \
../smartsoft/src-gen/VisionSkillImpl.cc \
../smartsoft/src-gen/main.cc 

CC_DEPS += \
./smartsoft/src-gen/TickHandlerCore.d \
./smartsoft/src-gen/VisionSkill.d \
./smartsoft/src-gen/VisionSkillImpl.d \
./smartsoft/src-gen/main.d 

OBJS += \
./smartsoft/src-gen/TickHandlerCore.o \
./smartsoft/src-gen/VisionSkill.o \
./smartsoft/src-gen/VisionSkillImpl.o \
./smartsoft/src-gen/main.o 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src-gen/%.o: ../smartsoft/src-gen/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/usr/local/src/robot/SmartSoft/include" -I"/usr/local/src/robot/SmartSoft/include/SmartSoft_CD_API" -I"/usr/local/src/robot/SmartSoft/include/AceSmartSoftKernel" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/Components/VisionSkill/smartsoft/src" -I"/usr/local/src/robot/yarp-smartsoft/Yarp-SmartSoft-Integration/Components/VisionSkill/smartsoft/src-gen" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


