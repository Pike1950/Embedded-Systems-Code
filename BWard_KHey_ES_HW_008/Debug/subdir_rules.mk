################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
HW8_KoleHey_BradWardcfg.cmd: ../HW8_KoleHey_BradWard.tcf
	@echo 'Building file: $<'
	@echo 'Invoking: TConf'
	"C:/ti/bios_5_42_01_09/xdctools/tconf" -b -Dconfig.importPath="C:/ti/bios_5_42_01_09/packages;" "$<"
	@echo 'Finished building: $<'
	@echo ' '

HW8_KoleHey_BradWardcfg.s??: | HW8_KoleHey_BradWardcfg.cmd
HW8_KoleHey_BradWardcfg_c.c: | HW8_KoleHey_BradWardcfg.cmd
HW8_KoleHey_BradWardcfg.h: | HW8_KoleHey_BradWardcfg.cmd
HW8_KoleHey_BradWardcfg.h??: | HW8_KoleHey_BradWardcfg.cmd
HW8_KoleHey_BradWard.cdb: | HW8_KoleHey_BradWardcfg.cmd

HW8_KoleHey_BradWardcfg.obj: ./HW8_KoleHey_BradWardcfg.s?? $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti2/ccsv6/tools/compiler/c6000_7.4.7/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti2/ccsv6/tools/compiler/c6000_7.4.7/include" --include_path="C:/Users/bradlwar/Documents/Fastlib/inc" --include_path="C:/Users/bradlwar/Documents/DSK6713/c6000/dsk6713/include" --include_path="C:/Users/bradlwar/Documents/DSK6713/c6000/bios/include" --include_path="C:/Users/bradlwar/Documents/HW8_KoleHey_BradWard/Debug" --include_path="C:/ti/bios_5_42_01_09/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_01_09/packages/ti/rtdx/include/c6000" --define=c6713 --define=CHIP_6713 --diag_wrap=off --diag_warning=225 --display_error_number --mem_model:const=far --mem_model:data=far --preproc_with_compile --preproc_dependency="HW8_KoleHey_BradWardcfg.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HW8_KoleHey_BradWardcfg_c.obj: ./HW8_KoleHey_BradWardcfg_c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti2/ccsv6/tools/compiler/c6000_7.4.7/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti2/ccsv6/tools/compiler/c6000_7.4.7/include" --include_path="C:/Users/bradlwar/Documents/Fastlib/inc" --include_path="C:/Users/bradlwar/Documents/DSK6713/c6000/dsk6713/include" --include_path="C:/Users/bradlwar/Documents/DSK6713/c6000/bios/include" --include_path="C:/Users/bradlwar/Documents/HW8_KoleHey_BradWard/Debug" --include_path="C:/ti/bios_5_42_01_09/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_01_09/packages/ti/rtdx/include/c6000" --define=c6713 --define=CHIP_6713 --diag_wrap=off --diag_warning=225 --display_error_number --mem_model:const=far --mem_model:data=far --preproc_with_compile --preproc_dependency="HW8_KoleHey_BradWardcfg_c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti2/ccsv6/tools/compiler/c6000_7.4.7/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti2/ccsv6/tools/compiler/c6000_7.4.7/include" --include_path="C:/Users/bradlwar/Documents/Fastlib/inc" --include_path="C:/Users/bradlwar/Documents/DSK6713/c6000/dsk6713/include" --include_path="C:/Users/bradlwar/Documents/DSK6713/c6000/bios/include" --include_path="C:/Users/bradlwar/Documents/HW8_KoleHey_BradWard/Debug" --include_path="C:/ti/bios_5_42_01_09/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_01_09/packages/ti/rtdx/include/c6000" --define=c6713 --define=CHIP_6713 --diag_wrap=off --diag_warning=225 --display_error_number --mem_model:const=far --mem_model:data=far --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


