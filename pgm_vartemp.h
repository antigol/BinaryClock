#ifndef PGM_VARTEMP_H
#define PGM_VARTEMP_H

#include "bc_program.h"
#include "bc_lm35.h"
#include "bc_lreg.h"

#define CUNTER_COMP 2000

class PGMVarTemp : public Program
{
private:
	uint16_t somme;
	uint8_t counter;
	uint8_t temperature;
	BCrgb color;
	Lreg lreg;
public:
	PGMVarTemp()
		: somme(0), counter(0)
	{
	}
	void init()
	{
		bc_flags |= (1<<Flag_Forever);
		lm35_on();
	}
	void uninit()
	{
		bc_flags &= ~(1<<Flag_Forever);
		lm35_off();
	}
	void forever()
	{
		bc_flags &= ~(1<<Flag_Forever);

		if (!lm35_isRunning()) {
			somme += lm35_value();
			if (++counter >= 200) {
				counter = 0;
				temperature = somme / 200;
				somme = 0;
				color = bc_tsl((temperature - 32) * (186 - 124) / 32 + 124);
			}
			lm35_start();
		}
	}
	uint16_t run()
	{
		bc_flags |= (1<<Flag_Forever);

		lreg.clear();
		lreg.addLeds(Lreg::ledsfortime(), color);
		return lreg.value();
	}
	uint16_t icon()
	{
		lreg.clear();
		lreg.addLeds(0b1111, color);
		return lreg.value();
	}
};

#endif /* PGM_VARTEMP_H */
