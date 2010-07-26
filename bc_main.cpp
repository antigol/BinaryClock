#include "bc_global.h"
#include "bc_io.h"
#include "bc_registers.h"
#include "bc_buttons.h"

#include "pgm_unicolor.h"
#include "pgm_tricolor.h"
#include "pgm_varteinte.h"
#include "pgm_vartemp.h"
#include "pgm_testcolor.h"
#include "pgm_circle.h"
#include "pgm_varsimple.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>

Program *pgm_list[10];			/* La liste des programme est déclarée ici pour pouvoir acceder facilement à sa taille */

int main()
{
	bc_prog_list = pgm_list;

	MCUSR &=~(1<<PORF);
	DDRB |= (1<<5);

	/*****************************************************/
	/****************** THE PROGRAMMES *******************/
	/*****************************************************/	

	init_tableau_rainbow();

	PGMVarSimple<3000> varsimple;
	PGMVarTeinte<250> teinte_lent;
	PGMVarTeinte<50> teinte_rapide;
	PGMCircle<250> circle;
	PGMVarTemp temperatureRB;
	PGMUnicolor test(BC::white);
	PGMTricolor redGreenBlue(BC::red, BC::green, BC::blue);
	PGMTricolor cyanmagentayellow(BC::cyan, BC::magenta, BC::yellow);
	PGMUnicolor sleepMode(bc_rgb(0, 0, 0));

/*
	PGMUnicolor white(BC::white);
	PGMCircle<100> circle;
	PGMUnicolor red(BC::red);
	PGMUnicolor green(BC::green);
	PGMUnicolor yellow(BC::yellow);
	PGMUnicolor magenta(BC::magenta);
	PGMTestcolor<BC::red> testr;
	PGMTestcolor<BC::green> testg;
	PGMTestcolor<BC::blue> testb;
*/	
	/*****************************************************/
	/****************** INITIALISATIONS ******************/
	/*****************************************************/
	bc_prog = 0;
	bc_prog_list[bc_prog]->init();				/* init the first program */

	init_registers();
	init_buttons();
	lm35_init();

	set_sleep_mode(SLEEP_MODE_PWR_SAVE);		/* set sleep mode */
	MCUCR |= (1<<5) | (1<<6);					/* /!\ */

	/*****************************************************/
	/***************** EXTERNAL INTERUPT *****************/
	/*****************************************************/
	EICRA = (1<<ISC01);
	EIMSK = (1<<INT0);
	SREG |= 0x80;								/* Global Interrupt Enable */

	/*****************************************************/
	/******************* TIMER CLOCK 2 *******************/
	/*******************   PAGE 155    *******************/
	/*****************************************************/
	ASSR 	|= 	(1<<AS2);						/* set asynchronous */

	TCCR2A 	= 	(1<<WGM21);						/* mode CTC */
	TCCR2B 	= 	(1<<CS22) | (1<<CS21);			/* 128 prescaler */
	OCR2A 	= 	127;

	TCNT2 	= 	0;								/* clear counter */
	TIMSK2 	= 	(1<<OCIE2A);					/* set interrupts=enabled */

	/*****************************************************/
	/****************** TIMER DISPLAY 0 ******************/
	/*****************************************************/
	TCCR0A = (1<<WGM01);          				/* Clear Timer on Compare (CTC) mode */	
	TCCR0B = 0x3;								/* Start timer with CS = 0b111 pre-scaler (Diviseur de clock)*/
	OCR0A  = 23;                  				/* f = 5220 Hz */
	TCNT0  = 0x00;								/* clear counter */
	TIMSK0 = (1<<OCIE0A);         				/* Enable oc-match-0a interrupt */

	MCUCR |= (1<<6);							/* /!\ */
	MCUCR &= ~(1<<5);							/* /!\ */

	while (true) {
		cli();
		if (bc_flags & (1<<Flag_Clock)) {
			bc_flags &= ~(1<<Flag_Clock);
			for (bc_i = 0; bc_i < 6; ++bc_i) {
				if (bc_i % 2)
					bc_cnums[bc_i] = bc_time[bc_i / 2] % 10;
				else
					bc_cnums[bc_i] = bc_time[bc_i / 2] / 10;
			}
		}

		if (bc_flags & (1<<Flag_Forever))
			bc_prog_list[bc_prog]->forever();		/* appelle la fonction forever du program en cours */
		sei();
	}
}
