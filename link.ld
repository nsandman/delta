OUTPUT_FORMAT("binary")  /* Output a flat binary for Pure64 */
ENTRY("start")

SECTIONS 
{
	.text :
	{
		*(.text)
		. = ALIGN(4K);
	}

	.data :
	{
		*(.data)
		*(.rodata)
		. = ALIGN(4K);
	}

	.bss :
	{
		*(.bss)
		. = ALIGN(4K);
	}
}