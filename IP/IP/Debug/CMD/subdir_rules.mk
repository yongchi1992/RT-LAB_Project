################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CMD/28335_RAM_lnk.exe: F:/control_1_new_20150210_06/IP/CMD/28335_RAM_lnk.cmd $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Linker'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml --float_support=softlib -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --obj_directory="F:/control_1_new_20150210_06/IP/Debug" -z --stack_size=1000 -m"F:/control_1_new_20150210_06/IP/CMD/Debug/IP.map" --heap_size=1000 --warn_sections -i"F:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" -i"F:/ti/ccsv5/tools/compiler/c2000_6.1.3/include" -i"F:/control_1_new_20150210_06/IP/IP" -i"F:/control_1_new_20150210_06/IP" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="IP_linkInfo.xml" --entry_point=code_start --rom_model -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMD/DSP2833x_Headers_nonBIOS.exe: F:/control_1_new_20150210_06/IP/CMD/DSP2833x_Headers_nonBIOS.cmd $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Linker'
	"F:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml --float_support=softlib -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --obj_directory="F:/control_1_new_20150210_06/IP/Debug" -z --stack_size=1000 -m"F:/control_1_new_20150210_06/IP/CMD/Debug/IP.map" --heap_size=1000 --warn_sections -i"F:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" -i"F:/ti/ccsv5/tools/compiler/c2000_6.1.3/include" -i"F:/control_1_new_20150210_06/IP/IP" -i"F:/control_1_new_20150210_06/IP" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="IP_linkInfo.xml" --entry_point=code_start --rom_model -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


