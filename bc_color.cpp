#include "bc_color.h"

#define RGB_MAX 31

BCrgb bc_tsl(uint8_t t, uint8_t l)
{
	const uint16_t tmax = 185;
	while (t > tmax)
		t -= tmax + 1;									/* t : [0;185] */

	const uint8_t lmax = 31;
	if (l > lmax)
		l = lmax;										/* l : [0;31] */

	const uint16_t rgbmax = RGB_MAX;

	const uint16_t t6 = 6 * (uint16_t)t;				/* [0; 1110] */

	const uint8_t to = t6 / (tmax + 1);				/* [0;5] */

	const uint16_t tn = t6 % (tmax + 1);				/* [0;185] */

	uint8_t rRed = 0;
	uint8_t rGreen = 0;
	uint8_t rBlue = 0;

	const uint8_t delta = (tn * rgbmax) / tmax;		/* 5735 / 185 = [0;31] */

	switch (to) {
	case 0:
		rRed = RGB_MAX;
		rGreen = delta;
		break;
	case 1:
		rRed = RGB_MAX - delta;
		rGreen = RGB_MAX;
		break;
	case 2:
		rGreen = RGB_MAX;
		rBlue = delta;
		break;
	case 3:
		rGreen = RGB_MAX - delta;
		rBlue = RGB_MAX;
		break;
	case 4:
		rRed = delta;
		rBlue = RGB_MAX;
		break;
	case 5:
		rRed = RGB_MAX;
		rBlue = RGB_MAX - delta;
		break;
	}
	const uint8_t lRed = (uint16_t)(rgbmax - rRed) * l / lmax;
	const uint8_t lGreen = (uint16_t)(rgbmax - rGreen) * l / lmax;
	const uint8_t lBlue = (uint16_t)(rgbmax - rBlue) * l / lmax;
	return bc_rgb(rRed + lRed, rGreen + lGreen, rBlue + lBlue);
}
