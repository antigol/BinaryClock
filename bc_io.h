/* Ports et pins de l'horloge binaire */
#ifndef BC_IO_H
#define BC_IO_H

#include <avr/io.h>

#define PORT_REG1	PORTD
#define DDR_REG1	DDRD
#define S_Clock		6		/* flanc montant */
#define C_Load		7		/* flanc montant */

#define PORT_REG2	PORTB
#define DDR_REG2	DDRB
#define L_Load		0		/* flanc montant */
#define S_Clear		2		/* flanc descendant */
#define S_Data		1		/* données */

#define PORT_STAT	PORTD
#define PIN_STAT	PIND
#define H_Power		2		/* allimentation secteur = 1 */

#define PORT_LM35	PORTC
#define DDR_LM35	DDRC
#define LM_Temp		0		/* ADC0 */

#define PORT_BUT	PORTC	/* buttons */
#define DDR_BUT		DDRC
#define PIN_BUT		PINC
#define B_Plus		2
#define B_Minus		3
#define B_Minute	4
#define B_Hour		5

#endif /* BC_IO_H */
