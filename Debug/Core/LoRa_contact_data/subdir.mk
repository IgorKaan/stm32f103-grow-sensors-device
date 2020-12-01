################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/LoRa_contact_data/LoRa_contact_data.cpp 

OBJS += \
./Core/LoRa_contact_data/LoRa_contact_data.o 

CPP_DEPS += \
./Core/LoRa_contact_data/LoRa_contact_data.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LoRa_contact_data/LoRa_contact_data.o: ../Core/LoRa_contact_data/LoRa_contact_data.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Packet_analyzer" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Exchange_packet" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa_contact_data" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa-module" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/my_lib" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_BME280" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa_contact_data/LoRa_contact_data.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
