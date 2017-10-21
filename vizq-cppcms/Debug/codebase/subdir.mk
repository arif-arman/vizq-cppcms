################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../codebase/mian.cpp \
../codebase/monotone.cpp \
../codebase/mvq.cpp \
../codebase/prevSource.cpp \
../codebase/vcm.cpp \
../codebase/vector3.cpp 

C_SRCS += \
../codebase/tinyfiledialogs.c 

OBJS += \
./codebase/mian.o \
./codebase/monotone.o \
./codebase/mvq.o \
./codebase/prevSource.o \
./codebase/tinyfiledialogs.o \
./codebase/vcm.o \
./codebase/vector3.o 

CPP_DEPS += \
./codebase/mian.d \
./codebase/monotone.d \
./codebase/mvq.d \
./codebase/prevSource.d \
./codebase/vcm.d \
./codebase/vector3.d 

C_DEPS += \
./codebase/tinyfiledialogs.d 


# Each subdirectory must supply rules for building sources it contributes
codebase/%.o: ../codebase/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

codebase/%.o: ../codebase/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


