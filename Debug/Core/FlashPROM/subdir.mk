################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/FlashPROM/FlashPROM.c 

C_DEPS += \
./Core/FlashPROM/FlashPROM.d 

OBJS += \
./Core/FlashPROM/FlashPROM.o 


# Each subdirectory must supply rules for building sources it contributes
Core/FlashPROM/FlashPROM.o: ../Core/FlashPROM/FlashPROM.c Core/FlashPROM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Sensor_CCS811" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/FlashPROM" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Grow_sensor" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Grow_sensor_component" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/LoRa_contact_data" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Sensor_BME280" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/FlashPROM/FlashPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

