################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/Log/LogMessage.cc \
../src/Log/Logger.cc \
../src/Log/PrintableLogs.cc 

CC_DEPS += \
./src/Log/LogMessage.d \
./src/Log/Logger.d \
./src/Log/PrintableLogs.d 

OBJS += \
./src/Log/LogMessage.o \
./src/Log/Logger.o \
./src/Log/PrintableLogs.o 


# Each subdirectory must supply rules for building sources it contributes
src/Log/%.o: ../src/Log/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/temp/eclipse-workspace/exampl3/src -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


