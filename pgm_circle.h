#ifndef PGM_CIRCLE_H
#define PGM_CIRCLE_H

#include "bc_program.h"
#include "bc_lreg.h"
#include "pgm_tableaux.h"

template <uint8_t periode>
class PGMCircle : public Program
{
private:
	uint8_t var;
	uint8_t clock;
	Lreg lreg;
public:
	PGMCircle()
		: var(0), clock(0)
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
		for (uint8_t i = 0; i < 4; ++i) {
			if (num & (1<<i)) {
				uint8_t id = rayons[4 * bc_creg + i] + var;
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
			uint8_t id = rayons[4 * bc_creg + i] + var;
			if (id >= 186)
				id -= 186;
			lreg.addLeds((1<<i), rainbow[id]);
		}
		return lreg.value();
	}
};

#endif /* PGM_CIRCLE_H */
