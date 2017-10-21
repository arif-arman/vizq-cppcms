################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../codebase/gpc/gpc.cpp 

OBJS += \
./codebase/gpc/gpc.o 

CPP_DEPS += \
./codebase/gpc/gpc.d 


# Each subdirectory must supply rules for building sources it contributes
codebase/gpc/%.o: ../codebase/gpc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


