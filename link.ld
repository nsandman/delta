/* On a weird note: Sublime Text users,
   choose Golang syntax highlighting for this 
   file. It doesn't look so depressingly
   blank, and it actually works!
   -n
*/

OUTPUT_FORMAT("binary")  /* Output a flat binary for Pure64 */
STARTUP("out/boot_asm.o")
ENTRY("start")

SECTIONS
{
	. = 0x100000;	/* Pure64 keeps all its data before this */
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
	end = .;	/* Kernel ending address */
}