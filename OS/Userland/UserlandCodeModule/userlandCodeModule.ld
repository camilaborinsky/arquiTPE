OUTPUT_FORMAT("binary")
ENTRY(_start)
SECTIONS
{
	.text 0x400000 :
	{
		*(.text*)
		. = ALIGN(0x1000);
	}
	.data ALIGN(0x1000) :
	{
		*(.data*)
		*(.rodata*)
	}
	.bss ALIGN(0x1000) :
	{
		bss = .;
		*(.bss*)
	}
	endOfBinary = .;
}