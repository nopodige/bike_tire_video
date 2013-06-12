################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include libs/lpc_core/lpc_ip/subdir.mk
-include libs/lpc_core/lpc_chip/chip_common/subdir.mk
-include libs/lpc_core/lpc_chip/chip_17xx_40xx/subdir.mk
-include libs/lpc_core/lpc_board/boards_17xx_40xx/ea_devkit_17884088/subdir.mk
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
led_test.hex \

SECONDARY_LIST += \
led_test.lst \

SECONDARY_SIZE += \
led_test.siz \


# All Target
all: led_test.elf secondary-outputs

# Tool invocations
led_test.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:/Users/Reed/Programming/bike_tire_video/tests/led_test/lpc17xx_gcc.ld" -nostartfiles -nodefaultlibs -nostdlib -Xlinker --gc-sections -Wl,-Map,led_test.map -mcpu=cortex-m3 -mthumb -o "led_test.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

led_test.hex: led_test.elf
	@echo 'Invoking: ARM Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex led_test.elf  "led_test.hex"
	@echo 'Finished building: $@'
	@echo ' '

led_test.lst: led_test.elf
	@echo 'Invoking: ARM Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S led_test.elf > "led_test.lst"
	@echo 'Finished building: $@'
	@echo ' '

led_test.siz: led_test.elf
	@echo 'Invoking: ARM Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley led_test.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) led_test.elf
	-@echo ' '

post-build:
	-arm-none-eabi-size  --format=berkeley led_test.elf & arm-none-eabi-objdump -S led_test.elf > "led_test.lst" & arm-none-eabi-objcopy -O ihex led_test.elf  "led_test.hex"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
