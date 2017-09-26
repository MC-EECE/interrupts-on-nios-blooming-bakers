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
	volatile int* interval_timer_ptr = (int*) 0x10002000; // interval timer base address
	volatile int* KEY_ptr = (int*) 0x10000050; // pushbutton KEY address
	int counter = 0x190000; // 1/(50 MHz)×(0x190000) = 33 msec
		*(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
	/* clear the interrupt */

	/* Act upon the interrupt */
	/* Display count value 
	 * (Is this the best place to do this? 
	 * Why or why not?) 
	 */
	HexDisplay((alt_u32*)HEX3_HEX0_BASE, *count_ptr);

	return;
}



