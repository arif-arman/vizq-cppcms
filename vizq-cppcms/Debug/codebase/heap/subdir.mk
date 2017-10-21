################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../codebase/heap/heap.cpp 

OBJS += \
./codebase/heap/heap.o 

CPP_DEPS += \
./codebase/heap/heap.d 


# Each subdirectory must supply rules for building sources it contributes
codebase/heap/%.o: ../codebase/heap/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


