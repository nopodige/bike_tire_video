################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
gpio_timer_example.hex \

SECONDARY_LIST += \
gpio_timer_example.lst \

SECONDARY_SIZE += \
gpio_timer_example.siz \


# All Target
all: gpio_timer_example.elf secondary-outputs

# Tool invocations
gpio_timer_example.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Windows GCC C Linker'
	arm-elf-gcc -nostartfiles -Wl,-Map,gpio_timer_example.map -mcpu=cortex-m4 -mthumb -o "gpio_timer_example.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

gpio_timer_example.hex: gpio_timer_example.elf
	@echo 'Invoking: ARM Windows GNU Create Flash Image'
	arm-elf-objcopy -O ihex gpio_timer_example.elf  "gpio_timer_example.hex"
	@echo 'Finished building: $@'
	@echo ' '

gpio_timer_example.lst: gpio_timer_example.elf
	@echo 'Invoking: ARM Windows GNU Create Listing'
	arm-elf-objdump -h -S gpio_timer_example.elf > "gpio_timer_example.lst"
	@echo 'Finished building: $@'
	@echo ' '

gpio_timer_example.siz: gpio_timer_example.elf
	@echo 'Invoking: ARM Windows GNU Print Size'
	arm-elf-size  --format=berkeley gpio_timer_example.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) gpio_timer_example.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
