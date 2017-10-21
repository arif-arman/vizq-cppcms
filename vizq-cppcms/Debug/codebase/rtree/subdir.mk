################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../codebase/rtree/distance.cpp \
../codebase/rtree/entry.cpp \
../codebase/rtree/rtnode.cpp \
../codebase/rtree/rtree.cpp \
../codebase/rtree/rtree_cmd.cpp 

OBJS += \
./codebase/rtree/distance.o \
./codebase/rtree/entry.o \
./codebase/rtree/rtnode.o \
./codebase/rtree/rtree.o \
./codebase/rtree/rtree_cmd.o 

CPP_DEPS += \
./codebase/rtree/distance.d \
./codebase/rtree/entry.d \
./codebase/rtree/rtnode.d \
./codebase/rtree/rtree.d \
./codebase/rtree/rtree_cmd.d 


# Each subdirectory must supply rules for building sources it contributes
codebase/rtree/%.o: ../codebase/rtree/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


