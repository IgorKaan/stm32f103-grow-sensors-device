################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/LoRa-module/Address_field.cpp \
../Core/LoRa-module/LoRa.cpp \
../Core/LoRa-module/LoRa_packet.cpp \
../Core/LoRa-module/LoRa_register.cpp \
../Core/LoRa-module/LoRa_register_data.cpp 

OBJS += \
./Core/LoRa-module/Address_field.o \
./Core/LoRa-module/LoRa.o \
./Core/LoRa-module/LoRa_packet.o \
./Core/LoRa-module/LoRa_register.o \
./Core/LoRa-module/LoRa_register_data.o 

CPP_DEPS += \
./Core/LoRa-module/Address_field.d \
./Core/LoRa-module/LoRa.d \
./Core/LoRa-module/LoRa_packet.d \
./Core/LoRa-module/LoRa_register.d \
./Core/LoRa-module/LoRa_register_data.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LoRa-module/Address_field.o: ../Core/LoRa-module/Address_field.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa-module" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/my_lib" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_BME280" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa-module/Address_field.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/LoRa-module/LoRa.o: ../Core/LoRa-module/LoRa.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa-module" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/my_lib" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_BME280" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa-module/LoRa.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/LoRa-module/LoRa_packet.o: ../Core/LoRa-module/LoRa_packet.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa-module" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/my_lib" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_BME280" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa-module/LoRa_packet.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/LoRa-module/LoRa_register.o: ../Core/LoRa-module/LoRa_register.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa-module" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/my_lib" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_BME280" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa-module/LoRa_register.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/LoRa-module/LoRa_register_data.o: ../Core/LoRa-module/LoRa_register_data.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa-module" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/my_lib" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_BME280" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/LoRa-module/LoRa_register_data.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
