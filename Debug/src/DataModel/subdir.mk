################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataModel/Calibration.cpp \
../src/DataModel/Color.cpp \
../src/DataModel/ColorClass.cpp \
../src/DataModel/Compass.cpp \
../src/DataModel/Features.cpp \
../src/DataModel/Matching.cpp \
../src/DataModel/Orientation.cpp \
../src/DataModel/Params.cpp 

OBJS += \
./src/DataModel/Calibration.o \
./src/DataModel/Color.o \
./src/DataModel/ColorClass.o \
./src/DataModel/Compass.o \
./src/DataModel/Features.o \
./src/DataModel/Matching.o \
./src/DataModel/Orientation.o \
./src/DataModel/Params.o 

CPP_DEPS += \
./src/DataModel/Calibration.d \
./src/DataModel/Color.d \
./src/DataModel/ColorClass.d \
./src/DataModel/Compass.d \
./src/DataModel/Features.d \
./src/DataModel/Matching.d \
./src/DataModel/Orientation.d \
./src/DataModel/Params.d 


# Each subdirectory must supply rules for building sources it contributes
src/DataModel/%.o: ../src/DataModel/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


