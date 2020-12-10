################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/LoRa_main_cpp/LoRa_main_file.cpp 

OBJS += \
./Core/LoRa_main_cpp/LoRa_main_file.o 

CPP_DEPS += \
./Core/LoRa_main_cpp/LoRa_main_file.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LoRa_main_cpp/LoRa_main_file.o: ../Core/LoRa_main_cpp/LoRa_main_file.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/FlashPROM" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_main_cpp" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor_component" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_contact_data" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa_main_cpp/LoRa_main_file.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

