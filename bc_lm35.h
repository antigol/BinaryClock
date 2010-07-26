#ifndef BC_LM35_H
#define BC_LM35_H

#include <inttypes.h>
#include <avr/io.h>

inline void lm35_on()				/* turn-on ADC */
{
	PRR &= ~(1<<PRADC);				/* recudtion de puissance désactivé -> AD on */
	ADCSRA |= (1<<ADEN);			/* enabled ADC */	
}

inline uint8_t lm35_isOn()
{
	return ADCSRA & (1<<ADEN);
}

inline void lm35_off()				/* turn-off ADC */
{
	PRR |= (1<<PRADC);
	ADCSRA &= ~(1<<ADEN);			/* disabled ADC */	
}

inline void lm35_start()			/* lance la mesure */
{
	ADCSRA |= (1<<ADSC);			/* lance la mesure */
}

inline uint8_t lm35_isRunning()
{
	return ADCSRA & (1<<ADSC);		/* vaut 1 pandant la mesure */
}

void lm35_wait();					/* attends la fin de la mesure */

inline uint8_t lm35_value()			/* retourne la 2 x temperature */
{
//	uint16_t brut = ADCL;
//	brut |= (ADCH<<8);
	return ADCW;					/* 40 correspond à 20°C */
}

void lm35_init();

#endif /* BC_LM35_H */

