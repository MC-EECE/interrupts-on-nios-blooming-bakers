/*
 * timerISR.c
 *
 *  Created on: 
 *      Author: 
 */
#include "System.h"
#include "alt_types.h"
#include "HexDisplay.h"

/*****************************************************************************
 * Interval timer interrupt service routine
 *
 *
******************************************************************************/

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void timerISR(void* context)

#else
void timerISR(void * context, alt_u32 id)

#endif
{
	/* Cast context. It is important that this be declared
	 * volatile to avoid unwanted compiler optimization.
	 */

	alt_u32* count_ptr = (alt_u32*)context;

	volatile int* interval_timer_ptr = (int*) INTERVAL_TIMER_BASE; // interval timer base address
	//olatile int* KEY_ptr = (int*) 0x10000050; // pushbutton KEY address

	/* clear the interrupt */

	*interval_timer_ptr = 0;
    // IOWR(INTERVAL_TIMER_BASE, 0, 1);

	/* Act upon the interrupt */
    *count_ptr = *count_ptr + 1;

	/* Display count value 
	 * (Is this the best place to do this? 
	 * Why or why not?) 
	 */

	HexDisplay((alt_u32*)HEX3_HEX0_BASE, *count_ptr);

	return;
}



