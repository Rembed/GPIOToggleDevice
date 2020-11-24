################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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
GpioToggleDeviceNucleoF722ZE.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
GpioToggleDeviceNucleoF722ZE.list \

OBJCOPY_BIN += \
GpioToggleDeviceNucleoF722ZE.bin \


# All Target
all: GpioToggleDeviceNucleoF722ZE.elf secondary-outputs

# Tool invocations
GpioToggleDeviceNucleoF722ZE.elf: $(OBJS) $(USER_OBJS) /home/michael/git_repos/SeniorProject/GPIOToggleDevice/STM32F722ZE_Nucleo_Implementation/GpioToggleDeviceNucleoF722ZE/STM32F722ZETX_FLASH.ld
	arm-none-eabi-gcc -o "GpioToggleDeviceNucleoF722ZE.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"/home/michael/git_repos/SeniorProject/GPIOToggleDevice/STM32F722ZE_Nucleo_Implementation/GpioToggleDeviceNucleoF722ZE/STM32F722ZETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="GpioToggleDeviceNucleoF722ZE.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

GpioToggleDeviceNucleoF722ZE.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "GpioToggleDeviceNucleoF722ZE.list"
	@echo 'Finished building: $@'
	@echo ' '

GpioToggleDeviceNucleoF722ZE.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "GpioToggleDeviceNucleoF722ZE.bin"
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
