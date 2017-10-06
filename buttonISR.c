/*
 * buttonISR.c
 *
 *  Created on: 
 *      Author: 
 */
#include "alt_types.h"
#include "io.h"
#include "system.h"
#include "HexDisplay.h"
#include "buttonISR.h"
#include "altera_avalon_pio_regs.h"
#include "lcd.h"
#include "sys\alt_irq.h"

#define KEY1 2
#define KEY2 4
#define KEY3 8

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void buttonISR(void* context)
#else
void buttonISR(void* context, alt_u32 id)
#endif
{
	alt_u8 timer_setting;

    /* Cast context It is important that this be declared 
     * volatile to avoid unwanted compiler optimization.
     */

	alt_u32* count_ptr = (alt_u32*)context;

	 /* Store the value in the PUSHBUTTONS's edge capture register (r3) in *context. */

	alt_u8 key = IORD(PUSHBUTTONS_BASE, 3);

    /* Reset the PUSHBUTTONS's edge capture register. */

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE,0);

    /* Act upon the interrupt */

    switch (key) {
    case 1: // should never get here because it is HW to reset
    	break;
    case KEY1: // KEY 1 was pressed
    	timer_setting = IORD(INTERVAL_TIMER_BASE,1);
    	if ((0x8&timer_setting) != 0) { // we are stopped, let's run now
    		timer_setting = 0x7; // This will make us run
    		LCD_cursor(0,0);
    		LCD_text("Counting..");
    	}
    	else { // we must be running
    		timer_setting = 0xB; // This will make us stop
    		LCD_cursor(0,0);
    		LCD_text("Stopped..");
    	}
    	IOWR(INTERVAL_TIMER_BASE,1,timer_setting);
    	break;
    case KEY2: // Key 2 was pressed
    	*count_ptr = 0;
    	HexDisplay((alt_u32*)HEX3_HEX0_BASE, *count_ptr);
    	LCD_cursor(0,1);
    	LCD_text("Button 2");
    	break;
    case KEY3: // Key 3 was pressed
    	toggleBCD();
    	HexDisplay((alt_u32*)HEX3_HEX0_BASE, *count_ptr);
    	LCD_cursor(0,1);
    	LCD_text("Button 3");
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
