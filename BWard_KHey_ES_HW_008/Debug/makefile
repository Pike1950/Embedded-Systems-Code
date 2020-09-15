################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti2/ccsv6/tools/compiler/c6000_7.4.7

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := -l"./HW8_KoleHey_BradWardcfg.cmd"

ORDERED_OBJS += \
"./HW8_KoleHey_BradWardcfg.obj" \
"./HW8_KoleHey_BradWardcfg_c.obj" \
"./main.obj" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"C:\Users\bradlwar\Documents\Fastlib\lib\c67xfastMath.lib" \
-l"C:\Users\bradlwar\Documents\DSK6713\c6000\bios\lib\csl6713.lib" \
-l"C:\Users\bradlwar\Documents\DSK6713\c6000\dsk6713\lib\dsk6713bsl.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
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
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
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
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
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
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
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
EXE_OUTPUTS += \
HW8_KoleHey_BradWard.out \

EXE_OUTPUTS__QUOTED += \
"HW8_KoleHey_BradWard.out" \

BIN_OUTPUTS += \
HW8_KoleHey_BradWard.hex \

BIN_OUTPUTS__QUOTED += \
"HW8_KoleHey_BradWard.hex" \


# All Target
all: HW8_KoleHey_BradWard.out

# Tool invocations
HW8_KoleHey_BradWard.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/ti2/ccsv6/tools/compiler/c6000_7.4.7/bin/cl6x" -mv6700 --abi=coffabi -g --define=c6713 --define=CHIP_6713 --diag_wrap=off --diag_warning=225 --display_error_number --mem_model:const=far --mem_model:data=far -z --stack_size=0x800 -m"HW8_KoleHey_BradWard.map" --heap_size=0x800 -i"C:/ti2/ccsv6/tools/compiler/c6000_7.4.7/lib" -i"C:/ti2/ccsv6/tools/compiler/c6000_7.4.7/include" -i"C:/ti/bios_5_42_01_09/packages/ti/rtdx/lib/c6000" -i"C:/ti/bios_5_42_01_09/packages/ti/bios/lib" --reread_libs --warn_sections --diag_wrap=off --display_error_number --xml_link_info="HW8_KoleHey_BradWard_linkInfo.xml" --rom_model -o "HW8_KoleHey_BradWard.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

HW8_KoleHey_BradWard.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C6000 Hex Utility'
	"C:/ti2/ccsv6/tools/compiler/c6000_7.4.7/bin/hex6x"  -o "HW8_KoleHey_BradWard.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_HDRS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(BIN_OUTPUTS__QUOTED)$(GEN_CMDS__QUOTED)
	-$(RM) "HW8_KoleHey_BradWardcfg_c.pp" "main.pp" 
	-$(RM) "HW8_KoleHey_BradWardcfg.pp" 
	-$(RM) "HW8_KoleHey_BradWardcfg.obj" "HW8_KoleHey_BradWardcfg_c.obj" "main.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

