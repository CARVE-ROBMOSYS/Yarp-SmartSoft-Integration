################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../OCamlWrap/wrap.c 

OBJS += \
./OCamlWrap/wrap.o 

C_DEPS += \
./OCamlWrap/wrap.d 


# Each subdirectory must supply rules for building sources it contributes
OCamlWrap/%.o: ../OCamlWrap/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


