OUTPUT_FORMAT("binary")  /* Output a flat binary for Pure64 */
STARTUP("out/boot_asm.o")
ENTRY("start")

SECTIONS 
{
	.text 0x100000 :
	{
		*(.text)
		*(.rodata)
		. = ALIGN(4K);
	}

	.data :
	{
		*(.data)
		. = ALIGN(4K);
	}

	.bss :
	{
		*(.bss)
		. = ALIGN(4K);
	}
}