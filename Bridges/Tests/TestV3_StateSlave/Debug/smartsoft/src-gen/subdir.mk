################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src-gen/TestV3_StateSlave.cc \
../smartsoft/src-gen/TestV3_StateSlaveImpl.cc \
../smartsoft/src-gen/main.cc 

CC_DEPS += \
./smartsoft/src-gen/TestV3_StateSlave.d \
./smartsoft/src-gen/TestV3_StateSlaveImpl.d \
./smartsoft/src-gen/main.d 

OBJS += \
./smartsoft/src-gen/TestV3_StateSlave.o \
./smartsoft/src-gen/TestV3_StateSlaveImpl.o \
./smartsoft/src-gen/main.o 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src-gen/%.o: ../smartsoft/src-gen/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


