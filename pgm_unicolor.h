#ifndef PGM_UNICOLOR_H
#define PGM_UNICOLOR_H

#include "bc_program.h"
#include "bc_lreg.h"

class PGMUnicolor : public Program
{
public:
	PGMUnicolor(const BCrgb &_color)
		: color(_color)
	{
	}
	void init()
	{
	}
	void uninit()
	{
	}
	uint16_t run()
	{
		lreg.clear(); 									/* objet qui aide a configurer lreg ( la valeur de retour ) */
		lreg.addLeds(Lreg::ledsfortime(), color); 		/* ajoute les leds 'num' en couleur 'color' */
		return lreg.value(); 							/* retourne la valeur de lreg ( uint16_t ) */
	}
	uint16_t icon()
	{
		lreg.clear();
		lreg.addLeds(0b1111, color); 					/* Allume toute les leds de couleur 'color' */
		return lreg.value(); 
	}
private:
	const BCrgb color; 									/* 0x0RGB */
	Lreg lreg;
};

#endif /* PGM_UNICOLOR_H */
