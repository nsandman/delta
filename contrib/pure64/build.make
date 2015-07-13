# The paths are all weird because this will be included 
# from the main Makefile in the repository root. These 
# targets are never used from this directory.

out/bmfs_mbr.sys: contrib/pure64/src/bootsectors/bmfs_mbr.asm
	$(call print_spc)
	@echo "$<\r[\033[1m$(ASM)\033[0m]"
	@$(ASM) -o$@ $<

# We only need this for network boot
# pxestart.sys: src/bootsectors/pxestart.asm
#	$(AASM) -o$@ $<

out/pure64.sys: contrib/pure64/src/pure64.asm
	$(call print_spc)
	@echo "$<\r[\033[1m$(ASM)\033[0m]"
	@cd contrib/pure64/src; \
	$(ASM) -o../../../$@ pure64.asm