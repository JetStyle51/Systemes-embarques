################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/TraceAnalyzer/trcInternalBuffer.c \
../Core/TraceAnalyzer/trcKernelPort.c \
../Core/TraceAnalyzer/trcSnapshotRecorder.c \
../Core/TraceAnalyzer/trcStreamingRecorder.c 

OBJS += \
./Core/TraceAnalyzer/trcInternalBuffer.o \
./Core/TraceAnalyzer/trcKernelPort.o \
./Core/TraceAnalyzer/trcSnapshotRecorder.o \
./Core/TraceAnalyzer/trcStreamingRecorder.o 

C_DEPS += \
./Core/TraceAnalyzer/trcInternalBuffer.d \
./Core/TraceAnalyzer/trcKernelPort.d \
./Core/TraceAnalyzer/trcSnapshotRecorder.d \
./Core/TraceAnalyzer/trcStreamingRecorder.d 


# Each subdirectory must supply rules for building sources it contributes
Core/TraceAnalyzer/trcInternalBuffer.o: ../Core/TraceAnalyzer/trcInternalBuffer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Core/Inc -I"C:/Users/SESA598592.EUR/Desktop/Systemes-embarques/RTOS/FreeRTOS/TraceAnalyzer/Core/TraceAnalyzer/config" -I"C:/Users/SESA598592.EUR/Desktop/Systemes-embarques/RTOS/FreeRTOS/TraceAnalyzer/Core/TraceAnalyzer/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/TraceAnalyzer/trcInternalBuffer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/TraceAnalyzer/trcKernelPort.o: ../Core/TraceAnalyzer/trcKernelPort.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Core/Inc -I"C:/Users/SESA598592.EUR/Desktop/Systemes-embarques/RTOS/FreeRTOS/TraceAnalyzer/Core/TraceAnalyzer/config" -I"C:/Users/SESA598592.EUR/Desktop/Systemes-embarques/RTOS/FreeRTOS/TraceAnalyzer/Core/TraceAnalyzer/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/TraceAnalyzer/trcKernelPort.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/TraceAnalyzer/trcSnapshotRecorder.o: ../Core/TraceAnalyzer/trcSnapshotRecorder.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Core/Inc -I"C:/Users/SESA598592.EUR/Desktop/Systemes-embarques/RTOS/FreeRTOS/TraceAnalyzer/Core/TraceAnalyzer/config" -I"C:/Users/SESA598592.EUR/Desktop/Systemes-embarques/RTOS/FreeRTOS/TraceAnalyzer/Core/TraceAnalyzer/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/TraceAnalyzer/trcSnapshotRecorder.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/TraceAnalyzer/trcStreamingRecorder.o: ../Core/TraceAnalyzer/trcStreamingRecorder.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Core/Inc -I"C:/Users/SESA598592.EUR/Desktop/Systemes-embarques/RTOS/FreeRTOS/TraceAnalyzer/Core/TraceAnalyzer/config" -I"C:/Users/SESA598592.EUR/Desktop/Systemes-embarques/RTOS/FreeRTOS/TraceAnalyzer/Core/TraceAnalyzer/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/TraceAnalyzer/trcStreamingRecorder.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

