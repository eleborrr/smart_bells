################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Server/Src/Entities/bell_settings.c \
../Core/Server/Src/Entities/edit_file_request.c \
../Core/Server/Src/Entities/edit_schedule.c \
../Core/Server/Src/Entities/empty.c \
../Core/Server/Src/Entities/file_entity.c \
../Core/Server/Src/Entities/schedule.c \
../Core/Server/Src/Entities/sync_time.c \
../Core/Server/Src/Entities/two_bells.c 

OBJS += \
./Core/Server/Src/Entities/bell_settings.o \
./Core/Server/Src/Entities/edit_file_request.o \
./Core/Server/Src/Entities/edit_schedule.o \
./Core/Server/Src/Entities/empty.o \
./Core/Server/Src/Entities/file_entity.o \
./Core/Server/Src/Entities/schedule.o \
./Core/Server/Src/Entities/sync_time.o \
./Core/Server/Src/Entities/two_bells.o 

C_DEPS += \
./Core/Server/Src/Entities/bell_settings.d \
./Core/Server/Src/Entities/edit_file_request.d \
./Core/Server/Src/Entities/edit_schedule.d \
./Core/Server/Src/Entities/empty.d \
./Core/Server/Src/Entities/file_entity.d \
./Core/Server/Src/Entities/schedule.d \
./Core/Server/Src/Entities/sync_time.d \
./Core/Server/Src/Entities/two_bells.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Server/Src/Entities/%.o Core/Server/Src/Entities/%.su Core/Server/Src/Entities/%.cyclo: ../Core/Server/Src/Entities/%.c Core/Server/Src/Entities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Server-2f-Src-2f-Entities

clean-Core-2f-Server-2f-Src-2f-Entities:
	-$(RM) ./Core/Server/Src/Entities/bell_settings.cyclo ./Core/Server/Src/Entities/bell_settings.d ./Core/Server/Src/Entities/bell_settings.o ./Core/Server/Src/Entities/bell_settings.su ./Core/Server/Src/Entities/edit_file_request.cyclo ./Core/Server/Src/Entities/edit_file_request.d ./Core/Server/Src/Entities/edit_file_request.o ./Core/Server/Src/Entities/edit_file_request.su ./Core/Server/Src/Entities/edit_schedule.cyclo ./Core/Server/Src/Entities/edit_schedule.d ./Core/Server/Src/Entities/edit_schedule.o ./Core/Server/Src/Entities/edit_schedule.su ./Core/Server/Src/Entities/empty.cyclo ./Core/Server/Src/Entities/empty.d ./Core/Server/Src/Entities/empty.o ./Core/Server/Src/Entities/empty.su ./Core/Server/Src/Entities/file_entity.cyclo ./Core/Server/Src/Entities/file_entity.d ./Core/Server/Src/Entities/file_entity.o ./Core/Server/Src/Entities/file_entity.su ./Core/Server/Src/Entities/schedule.cyclo ./Core/Server/Src/Entities/schedule.d ./Core/Server/Src/Entities/schedule.o ./Core/Server/Src/Entities/schedule.su ./Core/Server/Src/Entities/sync_time.cyclo ./Core/Server/Src/Entities/sync_time.d ./Core/Server/Src/Entities/sync_time.o ./Core/Server/Src/Entities/sync_time.su ./Core/Server/Src/Entities/two_bells.cyclo ./Core/Server/Src/Entities/two_bells.d ./Core/Server/Src/Entities/two_bells.o ./Core/Server/Src/Entities/two_bells.su

.PHONY: clean-Core-2f-Server-2f-Src-2f-Entities

