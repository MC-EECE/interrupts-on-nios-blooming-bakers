/*
 * buttonISR.c
 *
 *  Created on: 
 *      Author: 
 */

#include "buttonISR.h"
#include "altera_avalon_pio_regs.h"
#include "key_codes.h" // specify values for KEY1, KEY2 ?do we need this?


#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void buttonISR(void* context)
#else
void buttonISR(void* context, alt_u32 id)
#endif
{
    /* Cast context It is important that this be declared 
     * volatile to avoid unwanted compiler optimization.
     */

	volatileint* interval_timer_ptr = (int*) 0x10002000; // interval timer base address
	volatileint* KEY_ptr = (int*) 0x10000050; // pushbutton KEY address

    /* Store the value in the PUSHBUTTONS's edge capture register in *context. */

	*(KEY_ptr + 2) = 0xE; /* write to the pushbutton interrupt mask register,
						   *(KEY_ptr and * set 3 mask bits to 1 (bit 0 is Nios II reset) */

	intcounter = 0x190000; // 1/(50 MHz)×(0x190000) = 33 msec
	*(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1

    /* Reset the PUSHBUTTONS's edge capture register. */

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 0);

    /* Act upon the interrupt */

    while (KEY1 == 1)
    	*KEY_ptr = 0;

    *KEY_ptr == 1;

    if (KEY2 == 1)
    	*KEY_ptr = 0;
    	*interval_timer_ptr = 0;
    	*KEY_ptr = 1;

    if (KEY3 == 1)


    /*
     * Read the PIO to delay ISR exit. This is done to prevent a spurious
     * interrupt in systems with high processor -> pio latency and fast
     * interrupts.
     */

    IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE);
}
