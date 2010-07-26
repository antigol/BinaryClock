#include "bc_registers.h"
#include "bc_program.h"
#include "bc_global.h"
#include "bc_buttons.h"
#include "bc_io.h"
#include <avr/interrupt.h>

#define SHOWMAX 40000 // max : 65535
volatile uint16_t showicon;

/*****************************************************/
/***************** TIMER DISPLAY (0) *****************/
/*****************************************************/	
ISR(TIMER0_COMPA_vect)
{
	PORTB |= (1<<5);

	check_buttons();							/* gestion bouttons : hour, minute, plus, minus */

	if (pressed & ((1<<B_Hour) | (1<<B_Minute))) {
		showicon = 0;							/* stop la presntation du programme */
	}
	
	if ((pressed == (1<<B_Plus)) && (status == ((1<<B_Plus) | (1<<B_Hour)))) {
		if (++bc_time[Hour] >= 24)				/* incremente les heures */
			bc_time[Hour] = 0;
		bc_flags |= (1<<Flag_Clock);
	}
	if ((pressed == (1<<B_Plus)) && (status == ((1<<B_Plus) | (1<<B_Minute)))) {
		if (++bc_time[Minute] >= 60)			/* incremente les minutes */
			bc_time[Minute] = 0;
		bc_flags |= (1<<Flag_Clock);
	}
	if ((pressed == (1<<B_Minus)) && (status == ((1<<B_Minus) | (1<<B_Hour)))) {
		if (--bc_time[Hour] >= 24)				/* desincremente les heures */
			bc_time[Hour] = 23;
		bc_flags |= (1<<Flag_Clock);
	}
	if ((pressed == (1<<B_Minus)) && (status == ((1<<B_Minus) | (1<<B_Minute)))) {
		if (--bc_time[Minute] >= 60)			/* desincremente les heures */
			bc_time[Minute] = 59;
		bc_flags |= (1<<Flag_Clock);
	}
	if (status == ((1<<B_Hour) | (1<<B_Minute))) {
		bc_time[Second] = 0;
		TCNT2 = 0;								/* réinitialise le timer 2 */
		bc_flags |= (1<<Flag_Clock);
	}
	
	if ((pressed == (1<<B_Plus)) && (status == (1<<B_Plus))) {
		bc_prog_list[bc_prog]->uninit();		/* incremente le programme */
		if (++bc_prog >= bc_size_list)
			bc_prog = 0;
		showicon = SHOWMAX;
		bc_prog_list[bc_prog]->init();
	}
	if ((pressed == (1<<B_Minus)) && (status == (1<<B_Minus))) {
		bc_prog_list[bc_prog]->uninit();		/* desincremente le programme */
		if (bc_prog > 0)
			--bc_prog;
		else 
			bc_prog = bc_size_list - 1;
		showicon = SHOWMAX;
		bc_prog_list[bc_prog]->init();
	}

	if (++bc_creg >= 6)							/* incrementation de la colonne */
		bc_creg = 0;
	if (++bc_cregdiv[bc_creg] >= 31)			/* va de 0 à 30 et recommence */
		bc_cregdiv[bc_creg] = 0;

	uint16_t lreg;
	if (showicon) {
		//--showicon;							//TODO enlever le commentaire pour ne plus avoir d'icon infini
		lreg = bc_prog_list[bc_prog]->icon();
	} else {
		lreg = bc_prog_list[bc_prog]->run();
	}
												/* gestion registres à décalage */
	clear_C_register();
												/* ici : toutes les leds sont éteintes */
	set_L_register(lreg);
												/* ici : les leds sont prêtes à se faire allumées */
	set_C_register(bc_creg);
												/* ici : les leds sont r'allumées */

	PORTB &= ~(1<<5);
}
