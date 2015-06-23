# The paths are all weird because this will be included 
# from the main Makefile in the repository root. These 
# targets are never used from this directory.

out/bmfs_mbr.sys: contrib/pure64/src/bootsectors/bmfs_mbr.asm
	$(ASM) -o$@ $<

# We only need this for network boot
# pxestart.sys: src/bootsectors/pxestart.asm
#	$(AASM) -o$@ $<

out/pure64.sys: contrib/pure64/src/pure64.asm
	cd contrib/pure64/src; \
	$(ASM) -o../../../$@ pure64.asm