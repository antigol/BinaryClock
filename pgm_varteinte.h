#ifndef PGM_VARTEINTE_H
#define PGM_VARTEINTE_H

#include "bc_program.h"
#include "bc_lreg.h"
#include "pgm_tableaux.h"

template <uint8_t periode>
class PGMVarTeinte : public Program
{
private:
	uint8_t var;
	uint8_t clock;
	Lreg lreg;
public:
	PGMVarTeinte()
		: var(0), clock(0)
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
		if (++clock >= periode) {
			clock = 0;
			if (++var >= 186)
				var = 0;
		}

		const uint8_t num = Lreg::ledsfortime();

		lreg.clear();
		for (int8_t i = 0; i < 4; ++i) {
			if (num & (1<<i)) {
				uint8_t id = 8 * (i + bc_creg) + var;
				if (id >= 186)
					id -= 186;
				lreg.addLeds((1<<i), rainbow[id]);
			}
		}
		return lreg.value();
	}
	uint16_t icon()
	{
		if (++clock >= periode) {
			clock = 0;
			if (++var >= 186)
				var = 0;
		}

		lreg.clear();
		for (uint8_t i = 0; i < 4; ++i) {
			uint8_t id = 8 * (i + bc_creg) + var;
			if (id >= 186)
				id -= 186;
			lreg.addLeds((1<<i), rainbow[id]);
		}
		return lreg.value();
	}
};

#endif /* PGM_VARTEINTE_H */
