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
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


