################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Argv_Parser.cpp \
../Source/apps_string.cpp \
../Source/apps_times.cpp \
../Source/argparser.cpp \
../Source/localizate.cpp \
../Source/work.cpp 

OBJS += \
./Source/Argv_Parser.o \
./Source/apps_string.o \
./Source/apps_times.o \
./Source/argparser.o \
./Source/localizate.o \
./Source/work.o 

CPP_DEPS += \
./Source/Argv_Parser.d \
./Source/apps_string.d \
./Source/apps_times.d \
./Source/argparser.d \
./Source/localizate.d \
./Source/work.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_cplusplus=201103L -D__GXX_EXPERIMENTAL_CXX0X__ -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


