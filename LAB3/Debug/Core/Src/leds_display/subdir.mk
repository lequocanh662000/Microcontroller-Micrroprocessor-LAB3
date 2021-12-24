################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/leds_display/Functions_Light.c \
../Core/Src/leds_display/led_7seg_display.c 

OBJS += \
./Core/Src/leds_display/Functions_Light.o \
./Core/Src/leds_display/led_7seg_display.o 

C_DEPS += \
./Core/Src/leds_display/Functions_Light.d \
./Core/Src/leds_display/led_7seg_display.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/leds_display/%.o: ../Core/Src/leds_display/%.c Core/Src/leds_display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

