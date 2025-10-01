################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += \
./Src/Entities/bell_settings.o \
./Src/Entities/edit_file_request.o \
./Src/Entities/edit_schedule.o \
./Src/Entities/empty.o \
./Src/Entities/file_entity.o \
./Src/Entities/schedule.o \
./Src/Entities/sync_time.o \
./Src/Entities/two_bells.o 

C_DEPS += \
./Src/Entities/bell_settings.d \
./Src/Entities/edit_file_request.d \
./Src/Entities/edit_schedule.d \
./Src/Entities/empty.d \
./Src/Entities/file_entity.d \
./Src/Entities/schedule.d \
./Src/Entities/sync_time.d \
./Src/Entities/two_bells.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Entities/bell_settings.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Entities/bell_settings.c Src/Entities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Entities/edit_file_request.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Entities/edit_file_request.c Src/Entities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Entities/edit_schedule.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Entities/edit_schedule.c Src/Entities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Entities/empty.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Entities/empty.c Src/Entities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Entities/file_entity.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Entities/file_entity.c Src/Entities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Entities/schedule.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Entities/schedule.c Src/Entities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Entities/sync_time.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Entities/sync_time.c Src/Entities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Entities/two_bells.o: /home/elebor/STM32CubeIDE/workspace_1.12.0/F407_start/Core/Server/Src/Entities/two_bells.c Src/Entities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Entities

clean-Src-2f-Entities:
	-$(RM) ./Src/Entities/bell_settings.cyclo ./Src/Entities/bell_settings.d ./Src/Entities/bell_settings.o ./Src/Entities/bell_settings.su ./Src/Entities/edit_file_request.cyclo ./Src/Entities/edit_file_request.d ./Src/Entities/edit_file_request.o ./Src/Entities/edit_file_request.su ./Src/Entities/edit_schedule.cyclo ./Src/Entities/edit_schedule.d ./Src/Entities/edit_schedule.o ./Src/Entities/edit_schedule.su ./Src/Entities/empty.cyclo ./Src/Entities/empty.d ./Src/Entities/empty.o ./Src/Entities/empty.su ./Src/Entities/file_entity.cyclo ./Src/Entities/file_entity.d ./Src/Entities/file_entity.o ./Src/Entities/file_entity.su ./Src/Entities/schedule.cyclo ./Src/Entities/schedule.d ./Src/Entities/schedule.o ./Src/Entities/schedule.su ./Src/Entities/sync_time.cyclo ./Src/Entities/sync_time.d ./Src/Entities/sync_time.o ./Src/Entities/sync_time.su ./Src/Entities/two_bells.cyclo ./Src/Entities/two_bells.d ./Src/Entities/two_bells.o ./Src/Entities/two_bells.su

.PHONY: clean-Src-2f-Entities

