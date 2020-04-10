################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
user/cmd.obj: ../user/cmd.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: TMS470 Compiler'
	"C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv5e -g --define=omapl138 --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/ti/ti-cgt-arm_16.9.1.LTS/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/armv5/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/armv5" --diag_warning=225 -me --abi=eabi --code_state=32 --preproc_with_compile --preproc_dependency="user/cmd.pp" --obj_directory="user" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

user/main.obj: ../user/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: TMS470 Compiler'
	"C:/ti/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv5e -g --define=omapl138 --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/ti/ti-cgt-arm_16.9.1.LTS/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/armv5/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/armv5" --diag_warning=225 -me --abi=eabi --code_state=32 --preproc_with_compile --preproc_dependency="user/main.pp" --obj_directory="user" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


