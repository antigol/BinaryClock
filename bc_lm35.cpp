#include "bc_lm35.h"
#include "bc_io.h"

void lm35_wait()
{
	while (lm35_isRunning())
	{}
}

void lm35_init()
{
	ADMUX = (1<<REFS0); 				/* Vref : 5.0V */
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1);	/* set clock divisor */
	/* Input Channel Selections by default : 0000 -> ADC0 */
	DDR_LM35 &= ~(1<<LM_Temp);			/* entrée */
	PORT_LM35 &= ~(1<<LM_Temp);			/* sans pull-up */
}
