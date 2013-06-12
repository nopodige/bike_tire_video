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
-include libs/freertos/freertoslpc/subdir.mk
-include libs/freertos/freertos/Source/portable/MemMang/subdir.mk
-include libs/freertos/freertos/Source/portable/GCC/ARM_CM3/subdir.mk
-include libs/freertos/freertos/Source/subdir.mk
-include libs/filesystems/fatfslpc/subdir.mk
-include libs/filesystems/fatfs/src/subdir.mk
-include libs/LPCUSBLib/Drivers/USB/Core/HCD/OHCI/subdir.mk
-include libs/LPCUSBLib/Drivers/USB/Core/HCD/EHCI/subdir.mk
-include libs/LPCUSBLib/Drivers/USB/Core/HCD/subdir.mk
-include libs/LPCUSBLib/Drivers/USB/Core/HAL/LPC17XX/subdir.mk
-include libs/LPCUSBLib/Drivers/USB/Core/DCD/USBRom/subdir.mk
-include libs/LPCUSBLib/Drivers/USB/Core/DCD/LPC17XX/subdir.mk
-include libs/LPCUSBLib/Drivers/USB/Core/subdir.mk
-include libs/LPCUSBLib/Drivers/USB/Class/Host/subdir.mk
-include libs/LPCUSBLib/Drivers/USB/Class/Common/subdir.mk
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

SECONDARY_LIST += \

SECONDARY_SIZE += \


# All Target
all: usb_mass_storage_host.elf secondary-outputs

# Tool invocations
usb_mass_storage_host.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:/Users/Reed/Programming/bike_tire_video/tests/lpc1788_dev_board/usb_mass_storage_host/lpc17xx_gcc.ld" -nostartfiles -nodefaultlibs -nostdlib -Xlinker --gc-sections -Wl,-Map,usb_mass_storage_host.map -mcpu=cortex-m3 -mthumb -o "usb_mass_storage_host.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

usb_mass_storage_host.hex: usb_mass_storage_host.elf
	@echo 'Invoking: ARM Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex usb_mass_storage_host.elf  "usb_mass_storage_host.hex"
	@echo 'Finished building: $@'
	@echo ' '

usb_mass_storage_host.lst: usb_mass_storage_host.elf
	@echo 'Invoking: ARM Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S usb_mass_storage_host.elf > "usb_mass_storage_host.lst"
	@echo 'Finished building: $@'
	@echo ' '

usb_mass_storage_host.siz: usb_mass_storage_host.elf
	@echo 'Invoking: ARM Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley usb_mass_storage_host.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) usb_mass_storage_host.elf
	-@echo ' '

post-build:
	-arm-none-eabi-size  --format=berkeley usb_mass_storage_host.elf & arm-none-eabi-objdump -D usb_mass_storage_host.elf > "usb_mass_storage_host.lst" & arm-none-eabi-objcopy -O ihex usb_mass_storage_host.elf  "usb_mass_storage_host.hex"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
