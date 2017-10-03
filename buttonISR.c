/*
 * buttonISR.c
 *
 *  Created on: 
 *      Author: 
 */
#include "alt_types.h"
#include "io.h"
#include "system.h"
#include "buttonISR.h"
#include "altera_avalon_pio_regs.h"
#include "lcd.h"
#include "sys\alt_irq.h"

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void buttonISR(void* context)
#else
void buttonISR(void* context, alt_u32 id)
#endif
{
    /* Cast context It is important that this be declared 
     * volatile to avoid unwanted compiler optimization.
     */

	 /* Store the value in the PUSHBUTTONS's edge capture register (r3) in *context. */

    /* Reset the PUSHBUTTONS's edge capture register. */

    /* Act upon the interrupt */

	alt_u8 key = IORD(PUSHBUTTONS_BASE, 3);

    switch (key) {
    case 1: // should never get here because it is HW to reset
    	break;
    case 2: // KEY 1 was pressed
    	timer_setting = IORD(INTERVAL_TIMER_BASE,1);
    	if (timer_setting(0x3)) {
    		timer_setting = 0x7;
    		LCD_cursor = (0,0);
    		LCD_text("Counting..");
    	}
    	else {
    		timer_setting = 0x5;
    		LCD_cursor = (0,0);
    		LCD_text("Stopped..");
    	}
    	IOWR(INTERVAL_TIMER_BASE,1,timer_setting);
    	break;
    case 4: // Key 2 was pressed
    	*pcount = 0;
    	HexDisplay((alt_u32)HEX3_HEX0_BASE, pCount);
    	LCD_cursor = (0,1);
    	LCD_text("Button 2");
    	break;
    case 8: // Key 3 was pressed
    	toggleBCD();
    	LCD_cursor = (0,1);
    	LCD_text = ("Button 3");
    	break;
    default: // I have no idea how we got here
    	break;
    }

    /*
     * Read the PIO to delay ISR exit. This is done to prevent a spurious
     * interrupt in systems with high processor -> pio latency and fast
     * interrupts.
     */

    IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE);
}
