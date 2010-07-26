#include "bc_io.h"
#include "bc_global.h"
#include "bc_lm35.h"
#include "bc_registers.h"
#include "bc_program.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>

/*****************************************************/
/****************** TIMER CLOCK (2) ******************/
/*****************************************************/	
ISR(TIMER2_COMPA_vect)
{
	if (++bc_time[Second] >= 60) {
		bc_time[Second] = 0;
		if (++bc_time[Minute] >= 60) {
			bc_time[Minute] = 0;
			if (++bc_time[Hour] >= 24)
				bc_time[Hour] = 0;
		}
	}
	
	if (PIN_STAT & (1<<H_Power)) {
		if (bc_flags & (1<<Flag_Sleep)) {
			bc_prog_list[bc_prog]->init();
			TIMSK0 |= (1<<OCIE0A);				/* réactiver le timer 0 */
			bc_flags &= ~(1<<Flag_Sleep);
		}
	} else {
		sleep_enable();
		sei();
		sleep_cpu();
		sleep_disable();
	}

	bc_flags |= (1<<Flag_Clock);
}

/*****************************************************/
/***************** EXTERNAL INTERRUPT ****************/
/*****************************************************/	
ISR(INT0_vect)
{
	bc_flags |= (1<<Flag_Sleep);

	TIMSK0 &= ~(1<<OCIE0A);					/* desactiver le timer 0 */
	lm35_off();								/* desactive A-D Converter */
	clear_C_register();						/* clears registres */
	clear_L_register();

	bc_prog_list[bc_prog]->uninit();

	sleep_enable();
	sei();
	sleep_cpu();
	sleep_disable();
}
