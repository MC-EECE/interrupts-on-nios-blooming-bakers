/*
 * buttonISR.c
 *
 *  Created on: 
 *      Author: 
 */

#include "buttonISR.h"
#include "altera_avalon_pio_regs.h"
#include "key_codes.h" // specify values for KEY1, KEY2
#include<math.h>
#include<lcd.c>

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void buttonISR(void* context)
#else
void buttonISR(void* context, alt_u32 id)
#endif
{
    /* Cast context It is important that this be declared 
     * volatile to avoid unwanted compiler optimization.
     */

	int a=97, b=98, c=99,d=48;
	
    /* Store the value in the PUSHBUTTONS's edge capture register in *context. */

	*(KEY_ptr + 2) = 0xE; /* write to the pushbutton interrupt mask register,
						   *(KEY_ptr and * set 3 mask bits to 1 (bit 0 is Nios II reset) */


    /* Reset the PUSHBUTTONS's edge capture register. */

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 0);

    /* Act upon the interrupt */

    while (KEY1 == 1)
    {
    	*KEY_ptr = 0;
    	LCD_text(a);
    }
    
    *KEY_ptr == 1;
    
    if (KEY2 == 1)
    {
    	*KEY_ptr = 0;
    	*interval_timer_ptr = 0;
    	*KEY_ptr = 1;
    	LCD_text(b);
    }

    if (KEY3 == 1)
    {
    	int decimal_number = 0, remainder, hexadecimal_number;
    	      int count = 0;
    	      printf("Enter a Hexadecimal Number:\t");
    	      scanf("%d", &hexadecimal_number); 
    	      while(hexadecimal_number > 0)
    	      {
    	            remainder = hexadecimal_number % 10;
    	            decimal_number = decimal_number + remainder * pow(16, count);
    	            hexadecimal_number = hexadecimal_number / 10;
    	            count++;
    	      }
    	    	LCD_text(c);

    }

    /*
     * Read the PIO to delay ISR exit. This is done to prevent a spurious
     * interrupt in systems with high processor -> pio latency and fast
     * interrupts.
     */

    IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE);
}
