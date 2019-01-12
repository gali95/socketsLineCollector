################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/Server/Capabilities/BasicCapabilitiesImpl/SendAvailableLineCapability.cc \
../src/Server/Capabilities/BasicCapabilitiesImpl/SendAvailableLineNumberCapability.cc 

CC_DEPS += \
./src/Server/Capabilities/BasicCapabilitiesImpl/SendAvailableLineCapability.d \
./src/Server/Capabilities/BasicCapabilitiesImpl/SendAvailableLineNumberCapability.d 

OBJS += \
./src/Server/Capabilities/BasicCapabilitiesImpl/SendAvailableLineCapability.o \
./src/Server/Capabilities/BasicCapabilitiesImpl/SendAvailableLineNumberCapability.o 


# Each subdirectory must supply rules for building sources it contributes
src/Server/Capabilities/BasicCapabilitiesImpl/%.o: ../src/Server/Capabilities/BasicCapabilitiesImpl/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/temp/eclipse-workspace/exampl3/src -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


