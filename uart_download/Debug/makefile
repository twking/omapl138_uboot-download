################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ti-cgt-arm_16.9.1.LTS

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./spi_flash/util.obj" \
"./spi_flash/spiwriter.obj" \
"./spi_flash/spi_mem.obj" \
"./spi_flash/spi.obj" \
"./spi_flash/device_spi.obj" \
"./spi_flash/device.obj" \
"./spi_flash/debug.obj" \
"./user/main.obj" \
"./user/cmd.obj" \
"./xmodem/xmodem.obj" \
"./xmodem/crc16.obj" \
"../spiEdma.cmd" \
-l"libc.a" \
-ldrivers.lib \
-lplatform.lib \
-lsystem_config.lib \
-lutils.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include xmodem/subdir_vars.mk
-include user/subdir_vars.mk
-include spi_flash/subdir_vars.mk
-include subdir_rules.mk
-include xmodem/subdir_rules.mk
-include user/subdir_rules.mk
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
all: uart_download.out

# Tool invocations
uart_download.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: TMS470 Linker'
	"C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv5e -g --define=omapl138 --diag_warning=225 -me --abi=eabi --code_state=32 -z -m"uart_download.map" --stack_size=0x2000 --heap_size=0x2000 --define=omapl138 --diag_warning=225 --display_error_number --warn_sections -i"C:/ti/ti-cgt-arm_16.9.1.LTS/lib" -i"C:/ti/OMAPL138_StarterWare_1_10_04_01/binary/armv5/cgt_ccs/omapl138/system_config/Debug" -i"C:/ti/OMAPL138_StarterWare_1_10_04_01/binary/armv5/cgt_ccs/utils/Debug" -i"C:/ti/OMAPL138_StarterWare_1_10_04_01/binary/armv5/cgt_ccs/omapl138/drivers/Debug" -i"C:/ti/OMAPL138_StarterWare_1_10_04_01/binary/armv5/cgt_ccs/omapl138/evmOMAPL138/platform/Debug" -i"C:/ti/ti-cgt-arm_16.9.1.LTS/include" -i"C:/ti/ti-cgt-arm_16.9.1.LTS/lib" -i"C:/ti/ti-cgt-arm_16.9.1.LTS/include" --reread_libs --xml_link_info="uboot_uart_linkInfo.xml" --rom_model -o "uart_download.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(TMS470_EXECUTABLE_OUTPUTS__QUOTED) "uart_download.out"
	-$(RM) "xmodem\crc16.pp" "xmodem\xmodem.pp" "user\cmd.pp" "user\main.pp" "spi_flash\debug.pp" "spi_flash\device.pp" "spi_flash\device_spi.pp" "spi_flash\spi.pp" "spi_flash\spi_mem.pp" "spi_flash\spiwriter.pp" "spi_flash\util.pp" 
	-$(RM) "xmodem\crc16.obj" "xmodem\xmodem.obj" "user\cmd.obj" "user\main.obj" "spi_flash\debug.obj" "spi_flash\device.obj" "spi_flash\device_spi.obj" "spi_flash\spi.obj" "spi_flash\spi_mem.obj" "spi_flash\spiwriter.obj" "spi_flash\util.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'bin file'
	-"C:/ti/ccsv5/utils/tiobj2bin/tiobj2bin" "uart_download.out" "uart_download.bin" "C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armofd" "C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armhex" "C:/ti/ccsv5/utils/tiobj2bin/mkhex4bin" & "C:/ti/ccsv5/utils/tiobj2bin/tiobj2bin" "uart_download.out" "C:/24G_Radar_bin/normal_norflash_bin\load.bin" "C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armofd" "C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armhex" "C:/ti/ccsv5/utils/tiobj2bin/mkhex4bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

