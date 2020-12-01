################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Exchange_packet/Exchange_packet.cpp 

OBJS += \
./Core/Exchange_packet/Exchange_packet.o 

CPP_DEPS += \
./Core/Exchange_packet/Exchange_packet.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Exchange_packet/Exchange_packet.o: ../Core/Exchange_packet/Exchange_packet.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/Exchange_packet/Exchange_packet.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

