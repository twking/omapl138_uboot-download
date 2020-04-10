################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
spi_flash/device.obj: ../spi_flash/device.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv5e --code_state=32 -me --opt_for_speed=5 --include_path="C:/ti/ti-cgt-arm_16.9.1.LTS/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/armv5/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="spi_flash/device.pp" --obj_directory="spi_flash" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

spi_flash/device_spi.obj: ../spi_flash/device_spi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv5e --code_state=32 -me --opt_for_speed=5 --include_path="C:/ti/ti-cgt-arm_16.9.1.LTS/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/armv5/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="spi_flash/device_spi.pp" --obj_directory="spi_flash" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

spi_flash/spi.obj: ../spi_flash/spi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv5e --code_state=32 -me --opt_for_speed=5 --include_path="C:/ti/ti-cgt-arm_16.9.1.LTS/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/armv5/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="spi_flash/spi.pp" --obj_directory="spi_flash" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

spi_flash/spi_mem.obj: ../spi_flash/spi_mem.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv5e --code_state=32 -me --opt_for_speed=5 --include_path="C:/ti/ti-cgt-arm_16.9.1.LTS/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/armv5/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="spi_flash/spi_mem.pp" --obj_directory="spi_flash" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

spi_flash/spiwriter.obj: ../spi_flash/spiwriter.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv5e --code_state=32 -me --opt_for_speed=5 --include_path="C:/ti/ti-cgt-arm_16.9.1.LTS/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/armv5/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="spi_flash/spiwriter.pp" --obj_directory="spi_flash" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


