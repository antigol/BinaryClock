#ifndef PGM_VARSIMPLE_H
#define PGM_VARSIMPLE_H

#include "bc_program.h"
#include "bc_lreg.h"
#include "pgm_tableaux.h"

template <uint16_t periode>
class PGMVarSimple : public Program
{
private:
	uint8_t var;
	uint16_t clock;
	Lreg lreg;
public:
	PGMVarSimple()
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

		lreg.clear();
		lreg.addLeds(Lreg::ledsfortime(), rainbow[var]);

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
		lreg.addLeds(0xF, rainbow[var]);

		return lreg.value();
	}
};

#endif /* PGM_VARSIMPLE_H */
