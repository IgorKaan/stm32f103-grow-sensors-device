################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/my_lib/GrowTimer/GrowTimer_LoRa_module.c \
../Core/my_lib/GrowTimer/GrowTimer_device.c \
../Core/my_lib/GrowTimer/GrowTimer_sensor.c 

C_DEPS += \
./Core/my_lib/GrowTimer/GrowTimer_LoRa_module.d \
./Core/my_lib/GrowTimer/GrowTimer_device.d \
./Core/my_lib/GrowTimer/GrowTimer_sensor.d 

OBJS += \
./Core/my_lib/GrowTimer/GrowTimer_LoRa_module.o \
./Core/my_lib/GrowTimer/GrowTimer_device.o \
./Core/my_lib/GrowTimer/GrowTimer_sensor.o 


# Each subdirectory must supply rules for building sources it contributes
Core/my_lib/GrowTimer/GrowTimer_LoRa_module.o: ../Core/my_lib/GrowTimer/GrowTimer_LoRa_module.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa-module" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/my_lib" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_BME280" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/my_lib/GrowTimer/GrowTimer_LoRa_module.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/my_lib/GrowTimer/GrowTimer_device.o: ../Core/my_lib/GrowTimer/GrowTimer_device.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa-module" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/my_lib" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_BME280" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/my_lib/GrowTimer/GrowTimer_device.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/my_lib/GrowTimer/GrowTimer_sensor.o: ../Core/my_lib/GrowTimer/GrowTimer_sensor.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/LoRa-module" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/my_lib" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_BME280" -I"/home/igor/STM32CubeIDE/workspace_1.5.0/stm32f103-sensors-device/Core/Sensor_TSL2561" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/my_lib/GrowTimer/GrowTimer_sensor.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

