################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../smartsoft/src/tickers/GoalTicker.cpp \
../smartsoft/src/tickers/RelayTicker.cpp \
../smartsoft/src/tickers/SmartNavigTicker.cpp \
../smartsoft/src/tickers/SmartTicker.cpp \
../smartsoft/src/tickers/yarpTicker.cpp 

OBJS += \
./smartsoft/src/tickers/GoalTicker.o \
./smartsoft/src/tickers/RelayTicker.o \
./smartsoft/src/tickers/SmartNavigTicker.o \
./smartsoft/src/tickers/SmartTicker.o \
./smartsoft/src/tickers/yarpTicker.o 

CPP_DEPS += \
./smartsoft/src/tickers/GoalTicker.d \
./smartsoft/src/tickers/RelayTicker.d \
./smartsoft/src/tickers/SmartNavigTicker.d \
./smartsoft/src/tickers/SmartTicker.d \
./smartsoft/src/tickers/yarpTicker.d 


# Each subdirectory must supply rules for building sources it contributes
smartsoft/src/tickers/%.o: ../smartsoft/src/tickers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/usr/local/" -I"/home/icub/SOFTWARE/smartsoft_3.6/include" -I"/home/icub/SOFTWARE/smartsoft_3.6/include/SmartSoft_CD_API" -I"/home/icub/SOFTWARE/smartsoft_3.6/include/AceSmartSoftKernel" -I"/home/icub/SOFTWARE/smartsoft_3.6/Yarp-SmartSoft-Integration/BehaviorTree/BT_tickDispatcher/smartsoft/src" -I"/home/icub/SOFTWARE/smartsoft_3.6/Yarp-SmartSoft-Integration/BehaviorTree/BT_tickDispatcher/smartsoft/src-gen" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


