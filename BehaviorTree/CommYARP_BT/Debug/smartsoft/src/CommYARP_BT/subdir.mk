################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src/CommYARP_BT/CommTickCommand.cc \
../smartsoft/src/CommYARP_BT/CommTickResult.cc 

CC_DEPS += \
./smartsoft/src/CommYARP_BT/CommTickCommand.d \
./smartsoft/src/CommYARP_BT/CommTickResult.d 

OBJS += \
./smartsoft/src/CommYARP_BT/CommTickCommand.o \
./smartsoft/src/CommYARP_BT/CommTickResult.o 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src/CommYARP_BT/%.o: ../smartsoft/src/CommYARP_BT/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


