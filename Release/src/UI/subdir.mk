################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/UI/ScrollableCollectedLinesScreen.cc \
../src/UI/ScrollableDiscoveredAppsScreen.cc \
../src/UI/ScrollableLogScreen.cc \
../src/UI/ScrollableTextScreenI.cc 

CC_DEPS += \
./src/UI/ScrollableCollectedLinesScreen.d \
./src/UI/ScrollableDiscoveredAppsScreen.d \
./src/UI/ScrollableLogScreen.d \
./src/UI/ScrollableTextScreenI.d 

OBJS += \
./src/UI/ScrollableCollectedLinesScreen.o \
./src/UI/ScrollableDiscoveredAppsScreen.o \
./src/UI/ScrollableLogScreen.o \
./src/UI/ScrollableTextScreenI.o 


# Each subdirectory must supply rules for building sources it contributes
src/UI/%.o: ../src/UI/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/temp/eclipse-workspace/exampl3/src -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


