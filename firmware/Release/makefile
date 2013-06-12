################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/video_refresher/subdir.mk
-include src/sys/subdir.mk
-include src/position_monitor/subdir.mk
-include src/events/subdir.mk
-include src/display_refresher/subdir.mk
-include src/subdir.mk
-include libs/lpc_core/lpc_ip/subdir.mk
-include libs/lpc_core/lpc_chip/chip_common/subdir.mk
-include libs/lpc_core/lpc_chip/chip_17xx_40xx/subdir.mk
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
all: bike_tire_video.elf secondary-outputs

# Tool invocations
bike_tire_video.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:/Users/Reed/Programming/bike_tire_video/firmware/lpc17xx_gcc.ld" -nostartfiles -nodefaultlibs -nostdlib -Xlinker --gc-sections -Wl,-Map,bike_tire_video.map -mcpu=cortex-m3 -mthumb -o "bike_tire_video.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

bike_tire_video.hex: bike_tire_video.elf
	@echo 'Invoking: ARM Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex bike_tire_video.elf  "bike_tire_video.hex"
	@echo 'Finished building: $@'
	@echo ' '

bike_tire_video.lst: bike_tire_video.elf
	@echo 'Invoking: ARM Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S bike_tire_video.elf > "bike_tire_video.lst"
	@echo 'Finished building: $@'
	@echo ' '

bike_tire_video.siz: bike_tire_video.elf
	@echo 'Invoking: ARM Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley bike_tire_video.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) bike_tire_video.elf
	-@echo ' '

post-build:
	-arm-none-eabi-size  --format=berkeley bike_tire_video.elf & arm-none-eabi-objdump -S bike_tire_video.elf > "bike_tire_video.lst" & arm-none-eabi-objcopy -O ihex bike_tire_video.elf  "bike_tire_video.hex"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
