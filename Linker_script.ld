MEMORY
{
	flash(RX)	:ORIGIN	 = 0X08000000, LENGTH = 128K
	sram(RWX)	:ORIGIN	 = 0X20000000, LENGTH = 20K
}

SECTIONS
{
	.text : {
		*(.vectors*)
		*(.text*)
		*(.rodata*)
		_E_text = . ;  /*End text*/
		
	}> sram AT> flash /*VMA at s ram LMA at flash*/

	.data : {
	_S_Data = . ;  /* start data */
		
		*(.data*)
	_E_Data = . ;  /* End data */
	. = ALIGN(4);
		
	}> flash
	
	.bss : {
	_S_bss = . ;  /* start bss */
		*(.bss*)
		_E_bss = . ;  /* End bss */
		. = ALIGN(4);
		
		. = . + 0x1000;
		
		_stack_top = . ;
	} > sram
	
	
}