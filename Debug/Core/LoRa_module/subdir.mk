################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/LoRa_module/Address_field.cpp \
../Core/LoRa_module/LoRa.cpp \
../Core/LoRa_module/LoRa_packet.cpp \
../Core/LoRa_module/LoRa_register.cpp \
../Core/LoRa_module/LoRa_register_data.cpp 

OBJS += \
./Core/LoRa_module/Address_field.o \
./Core/LoRa_module/LoRa.o \
./Core/LoRa_module/LoRa_packet.o \
./Core/LoRa_module/LoRa_register.o \
./Core/LoRa_module/LoRa_register_data.o 

CPP_DEPS += \
./Core/LoRa_module/Address_field.d \
./Core/LoRa_module/LoRa.d \
./Core/LoRa_module/LoRa_packet.d \
./Core/LoRa_module/LoRa_register.d \
./Core/LoRa_module/LoRa_register_data.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LoRa_module/Address_field.o: ../Core/LoRa_module/Address_field.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/FlashPROM" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_main_cpp" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor_component" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_contact_data" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa_module/Address_field.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/LoRa_module/LoRa.o: ../Core/LoRa_module/LoRa.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/FlashPROM" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_main_cpp" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor_component" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_contact_data" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa_module/LoRa.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/LoRa_module/LoRa_packet.o: ../Core/LoRa_module/LoRa_packet.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/FlashPROM" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_main_cpp" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor_component" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_contact_data" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa_module/LoRa_packet.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/LoRa_module/LoRa_register.o: ../Core/LoRa_module/LoRa_register.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/FlashPROM" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_main_cpp" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor_component" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_contact_data" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa_module/LoRa_register.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/LoRa_module/LoRa_register_data.o: ../Core/LoRa_module/LoRa_register_data.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/FlashPROM" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_main_cpp" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Grow_sensor_component" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_module" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Packet_analyzer" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/LoRa_contact_data" -I"/home/igor/Desktop/СПИИРАН/Автономная теплица/23/stm32f103-grow-sensors-device-master/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O1 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa_module/LoRa_register_data.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

