#include "pgm_tableaux.h"
#include "bc_global.h"

BCrgb rainbow[186];

void init_tableau_rainbow()
{
	for (uint8_t i = 0; i < 186; ++i)
		rainbow[i] = bc_tsl(i);
}

#include <avr/pgmspace.h>

uint8_t rayons[24] =	/* id = 4 * bc_creg + lednumber */
{
	76,	72,	76,	87,
	54,	48,	54,	68,
	34,	24,	34,	54,
	24,	0,	24,	48,
	34,	24,	34,	54,
	54,	48,	54,	68
};
