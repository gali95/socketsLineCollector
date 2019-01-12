################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/Client/Requests/BasicRequestsImpl/AvailableLineNumberRequest.cc \
../src/Client/Requests/BasicRequestsImpl/AvailableLineRequest.cc 

CC_DEPS += \
./src/Client/Requests/BasicRequestsImpl/AvailableLineNumberRequest.d \
./src/Client/Requests/BasicRequestsImpl/AvailableLineRequest.d 

OBJS += \
./src/Client/Requests/BasicRequestsImpl/AvailableLineNumberRequest.o \
./src/Client/Requests/BasicRequestsImpl/AvailableLineRequest.o 


# Each subdirectory must supply rules for building sources it contributes
src/Client/Requests/BasicRequestsImpl/%.o: ../src/Client/Requests/BasicRequestsImpl/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/temp/eclipse-workspace/exampl3/src -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


