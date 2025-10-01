################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Server/Src/Handlers/bell_settings_handlers.c \
../Core/Server/Src/Handlers/file_handlers.c \
../Core/Server/Src/Handlers/schedule_handlers.c \
../Core/Server/Src/Handlers/sync_time_handler.c 

OBJS += \
./Core/Server/Src/Handlers/bell_settings_handlers.o \
./Core/Server/Src/Handlers/file_handlers.o \
./Core/Server/Src/Handlers/schedule_handlers.o \
./Core/Server/Src/Handlers/sync_time_handler.o 

C_DEPS += \
./Core/Server/Src/Handlers/bell_settings_handlers.d \
./Core/Server/Src/Handlers/file_handlers.d \
./Core/Server/Src/Handlers/schedule_handlers.d \
./Core/Server/Src/Handlers/sync_time_handler.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Server/Src/Handlers/%.o Core/Server/Src/Handlers/%.su Core/Server/Src/Handlers/%.cyclo: ../Core/Server/Src/Handlers/%.c Core/Server/Src/Handlers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Server-2f-Src-2f-Handlers

clean-Core-2f-Server-2f-Src-2f-Handlers:
	-$(RM) ./Core/Server/Src/Handlers/bell_settings_handlers.cyclo ./Core/Server/Src/Handlers/bell_settings_handlers.d ./Core/Server/Src/Handlers/bell_settings_handlers.o ./Core/Server/Src/Handlers/bell_settings_handlers.su ./Core/Server/Src/Handlers/file_handlers.cyclo ./Core/Server/Src/Handlers/file_handlers.d ./Core/Server/Src/Handlers/file_handlers.o ./Core/Server/Src/Handlers/file_handlers.su ./Core/Server/Src/Handlers/schedule_handlers.cyclo ./Core/Server/Src/Handlers/schedule_handlers.d ./Core/Server/Src/Handlers/schedule_handlers.o ./Core/Server/Src/Handlers/schedule_handlers.su ./Core/Server/Src/Handlers/sync_time_handler.cyclo ./Core/Server/Src/Handlers/sync_time_handler.d ./Core/Server/Src/Handlers/sync_time_handler.o ./Core/Server/Src/Handlers/sync_time_handler.su

.PHONY: clean-Core-2f-Server-2f-Src-2f-Handlers

