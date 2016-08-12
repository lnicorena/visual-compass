################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ImageDetection/ColorProcessing.cpp \
../src/ImageDetection/Histogram.cpp \
../src/ImageDetection/Processor.cpp 

OBJS += \
./src/ImageDetection/ColorProcessing.o \
./src/ImageDetection/Histogram.o \
./src/ImageDetection/Processor.o 

CPP_DEPS += \
./src/ImageDetection/ColorProcessing.d \
./src/ImageDetection/Histogram.d \
./src/ImageDetection/Processor.d 


# Each subdirectory must supply rules for building sources it contributes
src/ImageDetection/%.o: ../src/ImageDetection/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


