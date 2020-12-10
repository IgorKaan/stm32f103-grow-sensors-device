################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Packet_analyzer/Packet_analyzer.cpp 

OBJS += \
./Core/Packet_analyzer/Packet_analyzer.o 

CPP_DEPS += \
./Core/Packet_analyzer/Packet_analyzer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Packet_analyzer/Packet_analyzer.o: ../Core/Packet_analyzer/Packet_analyzer.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/FlashPROM" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_main_cpp" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor_component" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_contact_data" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/Packet_analyzer/Packet_analyzer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

