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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/FlashPROM" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor_component" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa_contact_data -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_contact_data" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Sensor_BME280" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Sensor_TSL2561/Sensor_TSL2561.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

