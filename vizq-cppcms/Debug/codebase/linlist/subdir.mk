################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../codebase/linlist/linlist.cpp 

OBJS += \
./codebase/linlist/linlist.o 

CPP_DEPS += \
./codebase/linlist/linlist.d 


# Each subdirectory must supply rules for building sources it contributes
codebase/linlist/%.o: ../codebase/linlist/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


