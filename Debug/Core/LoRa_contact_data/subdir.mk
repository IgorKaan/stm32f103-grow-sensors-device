################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/LoRa_contact_data/LoRa_contact_data.cpp 

OBJS += \
./Core/LoRa_contact_data/LoRa_contact_data.o 

CPP_DEPS += \
./Core/LoRa_contact_data/LoRa_contact_data.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LoRa_contact_data/LoRa_contact_data.o: ../Core/LoRa_contact_data/LoRa_contact_data.cpp Core/LoRa_contact_data/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Sensor_CCS811" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/FlashPROM" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/LoRa_main_cpp" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Grow_sensor" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Grow_sensor_component" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/LoRa_contact_data" -I"/home/igor/Downloads/Telegram Desktop/stm32f103-grow-sensors-device-master/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa_contact_data/LoRa_contact_data.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

