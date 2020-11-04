################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32_NUCLEO-F401RE_Assembler.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32_NUCLEO-F401RE_Assembler.list \

OBJCOPY_BIN += \
STM32_NUCLEO-F401RE_Assembler.bin \


# All Target
all: STM32_NUCLEO-F401RE_Assembler.elf secondary-outputs

# Tool invocations
STM32_NUCLEO-F401RE_Assembler.elf: $(OBJS) $(USER_OBJS) C:\Users\SESA598592\STM32CubeIDE\workspace_1.4.0\STM32_NUCLEO-F401RE_Assembler\STM32F401RETX_FLASH.ld
	arm-none-eabi-gcc -o "STM32_NUCLEO-F401RE_Assembler.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\SESA598592\STM32CubeIDE\workspace_1.4.0\STM32_NUCLEO-F401RE_Assembler\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32_NUCLEO-F401RE_Assembler.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32_NUCLEO-F401RE_Assembler.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32_NUCLEO-F401RE_Assembler.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32_NUCLEO-F401RE_Assembler.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32_NUCLEO-F401RE_Assembler.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
