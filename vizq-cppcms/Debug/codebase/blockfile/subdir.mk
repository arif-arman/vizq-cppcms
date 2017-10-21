################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../codebase/blockfile/blk_file.cpp \
../codebase/blockfile/cache.cpp 

OBJS += \
./codebase/blockfile/blk_file.o \
./codebase/blockfile/cache.o 

CPP_DEPS += \
./codebase/blockfile/blk_file.d \
./codebase/blockfile/cache.d 


# Each subdirectory must supply rules for building sources it contributes
codebase/blockfile/%.o: ../codebase/blockfile/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


