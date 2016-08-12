################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ImageProcessing/ColorProcessing.cpp \
../src/ImageProcessing/Histogram.cpp \
../src/ImageProcessing/ImageView.cpp \
../src/ImageProcessing/Processor.cpp 

OBJS += \
./src/ImageProcessing/ColorProcessing.o \
./src/ImageProcessing/Histogram.o \
./src/ImageProcessing/ImageView.o \
./src/ImageProcessing/Processor.o 

CPP_DEPS += \
./src/ImageProcessing/ColorProcessing.d \
./src/ImageProcessing/Histogram.d \
./src/ImageProcessing/ImageView.d \
./src/ImageProcessing/Processor.d 


# Each subdirectory must supply rules for building sources it contributes
src/ImageProcessing/%.o: ../src/ImageProcessing/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


