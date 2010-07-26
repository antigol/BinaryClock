#ifndef BC_LREG_H
#define BC_LREG_H
#include "bc_color.h"
#include "bc_global.h"

class Lreg
{
public:
	Lreg();
	inline uint16_t value() const
	{
		return lreg;
	}
	inline void clear()
	{
		lreg = 0;
	}
	void addLeds(uint8_t leds, const BCrgb color);
	static inline uint8_t ledsfortime()
	{
												/*
												 *         bc_time   bc_creg
												 * Hour    0         0 ou 1
												 * Minute  1         2 ou 3
												 * Second  2         4 ou 5
												 */
		return bc_cnums[bc_creg];
	}
private:
	uint16_t lreg;
};

#endif /* BC_LREG_H */
