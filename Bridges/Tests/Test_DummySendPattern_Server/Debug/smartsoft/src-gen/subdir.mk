################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../smartsoft/src-gen/BaseStateServiceInUpcallManager.cc \
../smartsoft/src-gen/Test_DummySendPattern_Server.cc \
../smartsoft/src-gen/Test_DummySendPattern_ServerImpl.cc \
../smartsoft/src-gen/main.cc 

CC_DEPS += \
./smartsoft/src-gen/BaseStateServiceInUpcallManager.d \
./smartsoft/src-gen/Test_DummySendPattern_Server.d \
./smartsoft/src-gen/Test_DummySendPattern_ServerImpl.d \
./smartsoft/src-gen/main.d 

OBJS += \
./smartsoft/src-gen/BaseStateServiceInUpcallManager.o \
./smartsoft/src-gen/Test_DummySendPattern_Server.o \
./smartsoft/src-gen/Test_DummySendPattern_ServerImpl.o \
./smartsoft/src-gen/main.o 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src-gen/%.o: ../smartsoft/src-gen/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


