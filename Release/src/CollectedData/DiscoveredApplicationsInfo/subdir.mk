################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/CollectedData/DiscoveredApplicationsInfo/DiscoveredApplications.cc 

CC_DEPS += \
./src/CollectedData/DiscoveredApplicationsInfo/DiscoveredApplications.d 

OBJS += \
./src/CollectedData/DiscoveredApplicationsInfo/DiscoveredApplications.o 


# Each subdirectory must supply rules for building sources it contributes
src/CollectedData/DiscoveredApplicationsInfo/%.o: ../src/CollectedData/DiscoveredApplicationsInfo/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/temp/eclipse-workspace/exampl3/src -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


