################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/Stubs/LinuxSockets.cc 

CC_DEPS += \
./src/Stubs/LinuxSockets.d 

OBJS += \
./src/Stubs/LinuxSockets.o 


# Each subdirectory must supply rules for building sources it contributes
src/Stubs/%.o: ../src/Stubs/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/temp/eclipse-workspace/exampl3/src -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


