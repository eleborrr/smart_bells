################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += \
./Src/Handlers/bell_settings_handlers.o \
./Src/Handlers/file_handlers.o \
./Src/Handlers/schedule_handlers.o \
./Src/Handlers/sync_time_handler.o 

C_DEPS += \
./Src/Handlers/bell_settings_handlers.d \
./Src/Handlers/file_handlers.d \
./Src/Handlers/schedule_handlers.d \
./Src/Handlers/sync_time_handler.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Handlers/bell_settings_handlers.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Handlers/bell_settings_handlers.c Src/Handlers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Handlers/file_handlers.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Handlers/file_handlers.c Src/Handlers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Handlers/schedule_handlers.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Handlers/schedule_handlers.c Src/Handlers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Handlers/sync_time_handler.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Handlers/sync_time_handler.c Src/Handlers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Handlers

clean-Src-2f-Handlers:
	-$(RM) ./Src/Handlers/bell_settings_handlers.cyclo ./Src/Handlers/bell_settings_handlers.d ./Src/Handlers/bell_settings_handlers.o ./Src/Handlers/bell_settings_handlers.su ./Src/Handlers/file_handlers.cyclo ./Src/Handlers/file_handlers.d ./Src/Handlers/file_handlers.o ./Src/Handlers/file_handlers.su ./Src/Handlers/schedule_handlers.cyclo ./Src/Handlers/schedule_handlers.d ./Src/Handlers/schedule_handlers.o ./Src/Handlers/schedule_handlers.su ./Src/Handlers/sync_time_handler.cyclo ./Src/Handlers/sync_time_handler.d ./Src/Handlers/sync_time_handler.o ./Src/Handlers/sync_time_handler.su

.PHONY: clean-Src-2f-Handlers

