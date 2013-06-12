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
-include libs/CMSIS/Device/ARM/ARMCM3/Source/GCC/subdir.mk
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
lpc1788_gcc_hello_world.hex \

SECONDARY_LIST += \
lpc1788_gcc_hello_world.lst \

SECONDARY_SIZE += \
lpc1788_gcc_hello_world.siz \


# All Target
all: lpc1788_gcc_hello_world.elf secondary-outputs

# Tool invocations
lpc1788_gcc_hello_world.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:\Users\Reed\Programming\bike_tire_video\firmware\libs\CMSIS\Device\ARM\ARMCM3\Source\GCC\gcc_arm.ld" -nostartfiles -nostdlib -Xlinker --gc-sections -Wl,-Map,lpc1788_gcc_hello_world.map -mcpu=cortex-m3 -mthumb -o "lpc1788_gcc_hello_world.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

lpc1788_gcc_hello_world.hex: lpc1788_gcc_hello_world.elf
	@echo 'Invoking: ARM Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex lpc1788_gcc_hello_world.elf  "lpc1788_gcc_hello_world.hex"
	@echo 'Finished building: $@'
	@echo ' '

lpc1788_gcc_hello_world.lst: lpc1788_gcc_hello_world.elf
	@echo 'Invoking: ARM Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S lpc1788_gcc_hello_world.elf > "lpc1788_gcc_hello_world.lst"
	@echo 'Finished building: $@'
	@echo ' '

lpc1788_gcc_hello_world.siz: lpc1788_gcc_hello_world.elf
	@echo 'Invoking: ARM Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley lpc1788_gcc_hello_world.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) lpc1788_gcc_hello_world.elf
	-@echo ' '

post-build:
	-arm-none-eabi-size  --format=berkeley lpc1788_gcc_hello_world.elf & arm-none-eabi-objdump -h -S lpc1788_gcc_hello_world.elf > "lpc1788_gcc_hello_world.lst" & arm-none-eabi-objcopy -O ihex lpc1788_gcc_hello_world.elf  "lpc1788_gcc_hello_world.hex"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
