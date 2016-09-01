################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tests/test_acc_spi_low_level.c \
../tests/test_adas1000_get_save_frame.c \
../tests/test_code_template.c \
../tests/test_configure_adas1000.c \
../tests/test_ecg_ring_buffer.c \
../tests/test_frame_ring_buffer.c \
../tests/test_global_runner.c \
../tests/test_spi_low_level.c \
../tests/unity.c 

OBJS += \
./tests/test_acc_spi_low_level.o \
./tests/test_adas1000_get_save_frame.o \
./tests/test_code_template.o \
./tests/test_configure_adas1000.o \
./tests/test_ecg_ring_buffer.o \
./tests/test_frame_ring_buffer.o \
./tests/test_global_runner.o \
./tests/test_spi_low_level.o \
./tests/unity.o 

C_DEPS += \
./tests/test_acc_spi_low_level.d \
./tests/test_adas1000_get_save_frame.d \
./tests/test_code_template.d \
./tests/test_configure_adas1000.d \
./tests/test_ecg_ring_buffer.d \
./tests/test_frame_ring_buffer.d \
./tests/test_global_runner.d \
./tests/test_spi_low_level.d \
./tests/unity.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ../tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32L476xx -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Inc" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Drivers/STM32L4xx_HAL_Driver/Inc" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Drivers/CMSIS/Include" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/workspace/ac6_mars_workspace/l476workspace/fromcube/rzhdv/rzhdv_01_01/rzhdv_01_01/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


