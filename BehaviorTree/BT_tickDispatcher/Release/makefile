################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include smartsoft/src/tickers/subdir.mk
-include smartsoft/src-gen/params/subdir.mk
-include smartsoft/src-gen/subdir.mk
-include smartsoft/src/subdir.mk
-include smartsoft/build/CMakeFiles/BT_tickDispatcher.dir/usr/local/src/robot/yarp-smartsoft/YARP-BT-modules/src/subdir.mk
-include smartsoft/build/CMakeFiles/BT_tickDispatcher.dir/src/tickers/subdir.mk
-include smartsoft/build/CMakeFiles/BT_tickDispatcher.dir/src-gen/params/subdir.mk
-include smartsoft/build/CMakeFiles/BT_tickDispatcher.dir/src-gen/subdir.mk
-include smartsoft/build/CMakeFiles/BT_tickDispatcher.dir/src/subdir.mk
-include smartsoft/build/CMakeFiles/3.12.20180920-g352399/CompilerIdCXX/subdir.mk
-include smartsoft/build/CMakeFiles/3.12.20180920-g352399/CompilerIdC/subdir.mk
-include smartsoft/build/CMakeFiles/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: BT_tickDispatcher

# Tool invocations
BT_tickDispatcher: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "BT_tickDispatcher" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) BT_tickDispatcher
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
