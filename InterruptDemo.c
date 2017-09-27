
#include "io.h"
#include "system.h"
#include "alt_types.h"
#include "sys\alt_irq.h"
#include "timerISR.h"

/*******************************************************************************
 * int main()                                                                  *
 *                                                                             *
 ******************************************************************************/

int main(void)
{ 
    /* Setup */

    /* Initialize Variables */


	static alt_u32 counter = 0;
	counter = 0; // 1/(50 MHz)×(0x190000) = 33 msec
	alt_u32* count_ptr = &counter;

    /* Register ISRs */

	alt_irq_register(INTERVAL_TIMER_IRQ, (void*)count_ptr, timerISR);

    /* Initialize Timer  Section 2.7 and 3.5*/


	IOWR(INTERVAL_TIMER_BASE, 2, 0x0000FFFF&INTERVAL_TIMER_FREQ);
	IOWR(INTERVAL_TIMER_BASE, 3, 0x0000FFFF&(INTERVAL_TIMER_FREQ >> 16));
	//IOWR_ALTERA_AVALON_TIMER_PERIODL(INTERVAL_TIMER_FREQ,0X9f00);
	//IOWR_ALTERA_AVALON_TIMER_PERIODH(INTERVAL_TIMER_FREQ,0X0024);

	IOWR(INTERVAL_TIMER_BASE, 1, 0x7); // STOP=0, START=1, CONT=1, ITO=1 => 0111b = 0x7
	//IOWR_ALTERA_AVALON_TIMER_CONTROL(INTERVAL_TIMER_FREQ,0X7);
	//IOWR_ALTERA_AVALON_TIMER_STATUS(INTERVAL_TIMER_FREQ,0);


    /* Loop while processing interrupts */
    while( 1 ) 
    {

    }
    return 0; // should never get here
}
