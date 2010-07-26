#include "bc_lreg.h"
#include <avr/pgmspace.h>
#include "bc_global.h"
/*^              x
**|             x
**|            xr
**|           x r
**|%         x r
**|t        x  r
**|i       x  r
**|m      x   r
**|e     x    r
**|     x    r
**|    x     r
**|   x    rr
**|  x  rrr
**| xrrr
**|x
**+-------------->
**     value
*/
/*
const uint8_t div_various[0xF] PROGMEM =
{
	0x0, 0xE, 0x7, 0x5, 0x9, 0x3, 0xB, 0x1, 
	0xD, 0x6, 0x8, 0x4, 0xA, 0x2, 0xC
};
*/
const uint8_t div_various[31] PROGMEM =
{
	26, 21, 18,  6, 29,  7,  1, 11, 
	20, 13,  2, 30, 14, 28, 23, 15,
	 9,  5, 12, 24,  4,  8,  3, 16,
	27, 17, 19,  0, 25, 10, 22,
};

Lreg::Lreg()
	: lreg(0)
{
}

void Lreg::addLeds(uint8_t leds, const BCrgb color)
{
	const uint8_t mod = pgm_read_byte(div_various + bc_cregdiv[bc_creg]);
	leds &= 0x0F;
	if (red(color) > mod) // R
		lreg |= (leds<<8);
	if (green(color) > mod) // G
		lreg |= (leds<<4);
	if (blue(color) > mod) // B
		lreg |= leds;
}

