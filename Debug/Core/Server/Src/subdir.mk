################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Server/Src/buffer.c \
../Core/Server/Src/esp.c \
../Core/Server/Src/list.c \
../Core/Server/Src/packet.c \
../Core/Server/Src/packet_handler.c \
../Core/Server/Src/parse_at.c \
../Core/Server/Src/serialize_utils.c \
../Core/Server/Src/server.c \
../Core/Server/Src/server_endpoints.c \
../Core/Server/Src/state_machine.c 

OBJS += \
./Core/Server/Src/buffer.o \
./Core/Server/Src/esp.o \
./Core/Server/Src/list.o \
./Core/Server/Src/packet.o \
./Core/Server/Src/packet_handler.o \
./Core/Server/Src/parse_at.o \
./Core/Server/Src/serialize_utils.o \
./Core/Server/Src/server.o \
./Core/Server/Src/server_endpoints.o \
./Core/Server/Src/state_machine.o 

C_DEPS += \
./Core/Server/Src/buffer.d \
./Core/Server/Src/esp.d \
./Core/Server/Src/list.d \
./Core/Server/Src/packet.d \
./Core/Server/Src/packet_handler.d \
./Core/Server/Src/parse_at.d \
./Core/Server/Src/serialize_utils.d \
./Core/Server/Src/server.d \
./Core/Server/Src/server_endpoints.d \
./Core/Server/Src/state_machine.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Server/Src/%.o Core/Server/Src/%.su Core/Server/Src/%.cyclo: ../Core/Server/Src/%.c Core/Server/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Core/Server/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Server-2f-Src

clean-Core-2f-Server-2f-Src:
	-$(RM) ./Core/Server/Src/buffer.cyclo ./Core/Server/Src/buffer.d ./Core/Server/Src/buffer.o ./Core/Server/Src/buffer.su ./Core/Server/Src/esp.cyclo ./Core/Server/Src/esp.d ./Core/Server/Src/esp.o ./Core/Server/Src/esp.su ./Core/Server/Src/list.cyclo ./Core/Server/Src/list.d ./Core/Server/Src/list.o ./Core/Server/Src/list.su ./Core/Server/Src/packet.cyclo ./Core/Server/Src/packet.d ./Core/Server/Src/packet.o ./Core/Server/Src/packet.su ./Core/Server/Src/packet_handler.cyclo ./Core/Server/Src/packet_handler.d ./Core/Server/Src/packet_handler.o ./Core/Server/Src/packet_handler.su ./Core/Server/Src/parse_at.cyclo ./Core/Server/Src/parse_at.d ./Core/Server/Src/parse_at.o ./Core/Server/Src/parse_at.su ./Core/Server/Src/serialize_utils.cyclo ./Core/Server/Src/serialize_utils.d ./Core/Server/Src/serialize_utils.o ./Core/Server/Src/serialize_utils.su ./Core/Server/Src/server.cyclo ./Core/Server/Src/server.d ./Core/Server/Src/server.o ./Core/Server/Src/server.su ./Core/Server/Src/server_endpoints.cyclo ./Core/Server/Src/server_endpoints.d ./Core/Server/Src/server_endpoints.o ./Core/Server/Src/server_endpoints.su ./Core/Server/Src/state_machine.cyclo ./Core/Server/Src/state_machine.d ./Core/Server/Src/state_machine.o ./Core/Server/Src/state_machine.su

.PHONY: clean-Core-2f-Server-2f-Src

