################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Sensor_TSL2561/Sensor_TSL2561.c 

C_DEPS += \
./Core/Sensor_TSL2561/Sensor_TSL2561.d 

OBJS += \
./Core/Sensor_TSL2561/Sensor_TSL2561.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Sensor_TSL2561/Sensor_TSL2561.o: ../Core/Sensor_TSL2561/Sensor_TSL2561.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Sensor_TSL2561/Sensor_TSL2561.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

