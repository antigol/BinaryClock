#ifndef PGM_TESTCOLOR_H
#define PGM_TESTCOLOR_H

#include "bc_program.h"
#include "bc_lreg.h"

template <BCrgb rgb>
class PGMTestcolor : public Program
{
private:
	Lreg lreg;
public:
	PGMTestcolor()
	{
	}
	uint16_t run()
	{
		lreg.clear();
		for (uint8_t i = 0; i < 4; ++i) {
			uint8_t col = 6 * i + bc_creg;
			if (col > 11)
				++col;
			if (col >= 32)
				col = 0;
			BCrgb color = bc_rgb(col, col, col);
			color &= rgb;
			lreg.addLeds((1<<i), color);
		}
		return lreg.value();
	}
};

#endif /* PGM_TESTCOLOR_H */
