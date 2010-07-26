#ifndef PGM_TRICOLOR_H
#define PGM_TRICOLOR_H

#include "bc_program.h"
#include "bc_lreg.h"

class PGMTricolor : public Program
{
public:
	PGMTricolor(const BCrgb &_color_hour, const BCrgb &_color_minute, const BCrgb &_color_second)
	{
		color[0] = _color_hour;
		color[1] = _color_minute;
		color[2] = _color_second;
	}
	void init()
	{
	}
	void uninit()
	{
	}
	uint16_t run()
	{
		lreg.clear();
		lreg.addLeds(Lreg::ledsfortime(), color[bc_creg/2]);
		return lreg.value();
	}
	uint16_t icon()
	{
		lreg.clear();
		lreg.addLeds(0b1111, color[bc_creg/2]);
		return lreg.value(); 
	}
private:
	BCrgb color[3];
	Lreg lreg;
};

#endif /* PGM_TRICOLOR_H */
