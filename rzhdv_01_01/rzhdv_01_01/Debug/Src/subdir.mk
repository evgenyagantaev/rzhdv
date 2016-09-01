################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/acc_spi_low_level.c \
../Src/adas1000.c \
../Src/adas1000_get_save_frame.c \
../Src/adc.c \
../Src/configure_adas1000.c \
../Src/crc.c \
../Src/ecg_ring_buffer.c \
../Src/frame_ring_buffer.c \
../Src/frame_ring_buffer_task.c \
../Src/freertos.c \
../Src/gpio.c \
../Src/iwdg.c \
../Src/putchar.c \
../Src/spi.c \
../Src/spi_low_level.c \
../Src/stm32l4xx_hal_msp.c \
../Src/stm32l4xx_hal_timebase_TIM.c \
../Src/stm32l4xx_it.c \
../Src/tim.c \
../Src/timer250hz.c \
../Src/timer250hz_irqhandler.c \
../Src/usart.c \
../Src/usbd_conf.c \
../Src/usbd_desc.c 

OBJS += \
./Src/acc_spi_low_level.o \
./Src/adas1000.o \
./Src/adas1000_get_save_frame.o \
./Src/adc.o \
./Src/configure_adas1000.o \
./Src/crc.o \
./Src/ecg_ring_buffer.o \
./Src/frame_ring_buffer.o \
./Src/frame_ring_buffer_task.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/iwdg.o \
./Src/putchar.o \
./Src/spi.o \
./Src/spi_low_level.o \
./Src/stm32l4xx_hal_msp.o \
./Src/stm32l4xx_hal_timebase_TIM.o \
./Src/stm32l4xx_it.o \
./Src/tim.o \
./Src/timer250hz.o \
./Src/timer250hz_irqhandler.o \
./Src/usart.o \
./Src/usbd_conf.o \
./Src/usbd_desc.o 

C_DEPS += \
./Src/acc_spi_low_level.d \
./Src/adas1000.d \
./Src/adas1000_get_save_frame.d \
./Src/adc.d \
./Src/configure_adas1000.d \
./Src/crc.d \
./Src/ecg_ring_buffer.d \
./Src/frame_ring_buffer.d \
./Src/frame_ring_buffer_task.d \
./Src/freertos.d \
./Src/gpio.d \
./Src/iwdg.d \
./Src/putchar.d \
./Src/spi.d \
./Src/spi_low_level.d \
./Src/stm32l4xx_hal_msp.d \
./Src/stm32l4xx_hal_timebase_TIM.d \
./Src/stm32l4xx_it.d \
./Src/tim.d \
./Src/timer250hz.d \
./Src/timer250hz_irqhandler.d \
./Src/usart.d \
./Src/usbd_conf.d \
./Src/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L476xx -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Inc" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Drivers/STM32L4xx_HAL_Driver/Inc" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Drivers/CMSIS/Include" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


