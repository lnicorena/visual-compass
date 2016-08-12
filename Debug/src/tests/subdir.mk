################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tests/BlobTests.cpp \
../src/tests/ColorReduction.cpp \
../src/tests/DetectRedObj.cpp \
../src/tests/Helper.cpp \
../src/tests/HsvTests.cpp \
../src/tests/LoadImage.cpp \
../src/tests/Perfomance.cpp 

OBJS += \
./src/tests/BlobTests.o \
./src/tests/ColorReduction.o \
./src/tests/DetectRedObj.o \
./src/tests/Helper.o \
./src/tests/HsvTests.o \
./src/tests/LoadImage.o \
./src/tests/Perfomance.o 

CPP_DEPS += \
./src/tests/BlobTests.d \
./src/tests/ColorReduction.d \
./src/tests/DetectRedObj.d \
./src/tests/Helper.d \
./src/tests/HsvTests.d \
./src/tests/LoadImage.d \
./src/tests/Perfomance.d 


# Each subdirectory must supply rules for building sources it contributes
src/tests/%.o: ../src/tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


