################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ti-cgt-arm_16.9.1.LTS

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./spi_flash/spiwriter.obj" \
"./spi_flash/spi_mem.obj" \
"./spi_flash/spi.obj" \
"./spi_flash/device_spi.obj" \
"./spi_flash/device.obj" \
"./main.obj" \
"./dev_uart.obj" \
"../OMAPL138.cmd" \
-lplatform.lib \
-l"C:\ti\OMAPL138_StarterWare_1_10_04_01\binary\armv5\cgt_ccs\omapl138\drivers\Debug\drivers.lib" \
-lsystem_config.lib \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include spi_flash/subdir_vars.mk
-include subdir_rules.mk
-include spi_flash/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: uboot_uart.out

# Tool invocations
uboot_uart.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv5e --code_state=32 -me --opt_for_speed=5 --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"uboot_uart.map" --heap_size=0x400 --stack_size=0x400 -i"C:/ti/ti-cgt-arm_16.9.1.LTS/lib" -i"C:/ti/OMAPL138_StarterWare_1_10_04_01/binary/armv5/cgt_ccs/omapl138/evmOMAPL138/platform/Debug" -i"C:/ti/OMAPL138_StarterWare_1_10_04_01/binary/armv5/cgt_ccs/omapl138/system_config/Debug" -i"C:/ti/ti-cgt-arm_16.9.1.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="uboot_uart_linkInfo.xml" --rom_model -o "uboot_uart.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(TMS470_EXECUTABLE_OUTPUTS__QUOTED) "uboot_uart.out"
	-$(RM) "dev_uart.pp" "main.pp" "spi_flash\device.pp" "spi_flash\device_spi.pp" "spi_flash\spi.pp" "spi_flash\spi_mem.pp" "spi_flash\spiwriter.pp" 
	-$(RM) "dev_uart.obj" "main.obj" "spi_flash\device.obj" "spi_flash\device_spi.obj" "spi_flash\spi.obj" "spi_flash\spi_mem.obj" "spi_flash\spiwriter.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

