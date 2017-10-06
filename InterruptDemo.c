
#include "io.h"
#include "system.h"
#include "alt_types.h"
#include "sys\alt_irq.h"
#include "timerISR.h"
#include "buttonISR.h"

/*******************************************************************************
 * int main()                                                                  *
 *                                                                             *
 ******************************************************************************/

int main(void)
{ 
    /* Setup */

    /* Initialize Variables */


	static alt_u32 counter = 0;
	counter = 0;
	alt_u32* count_ptr = &counter;

    /* Register ISRs */

	alt_irq_register(INTERVAL_TIMER_IRQ, (void*)count_ptr, timerISR);
	alt_irq_register(PUSHBUTTONS_IRQ,(void*)count_ptr, buttonISR);

    /* Initialize Timer */

	IOWR(INTERVAL_TIMER_BASE, 2, 0x0000FFFF&INTERVAL_TIMER_FREQ);
	IOWR(INTERVAL_TIMER_BASE, 3, 0x0000FFFF&(INTERVAL_TIMER_FREQ >> 16));

	IOWR(INTERVAL_TIMER_BASE, 1, 0x7); // STOP=0, START=1, CONT=1, ITO=1 => 0111b = 0x7

	/* Initialize Pushbuttons */

	IOWR(PUSHBUTTONS_BASE,2,0xE); //111b = 0xE

    /* Loop while processing interrupts */
    while( 1 ) 
    {
    	//IOWR(RED_LED_BASE,0,1);
    }
    return 0; // should never get here
}
