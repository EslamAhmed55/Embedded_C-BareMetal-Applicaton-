// startup.c
//copy (data and create .bss sections)
//Vector Handller
#include <stdint.h>

void Reset_Handler();
extern	int main(void);

void Defualt_Handler()
{
	Reset_Handler();
}

void NMI_Handler()__attribute__((weak,alias("Defualt_Handler")));;
void H_Fault_Handler()__attribute__((weak,alias("Defualt_Handler")));;
void MM_Fualt_Handler()__attribute__((weak,alias("Defualt_Handler")));;
void Bus_Handler()__attribute__((weak,alias("Defualt_Handler")));;
void Usage_Fualt_Handler()__attribute__((weak,alias("Defualt_Handler")));;

extern unsigned int _stack_top;

uint32_t vectors[]__attribute__((section(".vectors"))) ={
	
	(uint32_t) &_stack_top,
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_Fault_Handler,
	(uint32_t) &MM_Fualt_Handler,
	(uint32_t) &Bus_Handler,
	(uint32_t) &Usage_Fualt_Handler




};

extern unsigned int _E_text ;
extern unsigned int _S_Data ;
extern unsigned int _E_Data ;
extern unsigned int _S_bss ;
extern unsigned int _E_bss ;


void Reset_Handler(void)
{
	// copy (data form flash to ram ) 
	
	unsigned int DATA_size = (unsigned char *) &_E_Data -  (unsigned char *) _S_Data;  // copy byte by byte
	
	unsigned char * P_scr =(unsigned char *) &_E_text;
		unsigned char * P_dst =(unsigned char *) &_S_Data;
		
		for (int i=0; i< DATA_size ; i++)
		{
			*((unsigned char *)P_dst++) = *((unsigned char *)P_scr++);
		}
		
		// create .bss sections
		
		unsigned char bss_size =(unsigned char *)& _E_bss - (unsigned char *)& _S_bss;
		
		P_dst=(unsigned char *) & _S_bss;
		
		for (int i=0; i< bss_size ; i++)
		{
			*((unsigned char *)P_dst++) = (unsigned char)0;
			
		}
		
		
		//jump main()
		
	
	main();
	
}

