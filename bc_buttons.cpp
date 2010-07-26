#include "bc_buttons.h"
#include "bc_io.h"
#include "bc_global.h"
// global
const uint8_t high_lvl = 60;
uint8_t status = 0;
uint8_t pressed = 0;
uint8_t release = 0;
const uint16_t high_flood = 2600;


uint8_t trigger[4];
uint16_t flood[4];
uint8_t status1;

void init_buttons()
{
	for (uint8_t i = 0; i < 4; ++i) {
		trigger[i] = 0;
		flood[i] = 0;
	}
	DDR_BUT &= ~((1<<B_Plus) | (1<<B_Minus) | (1<<B_Hour) | (1<<B_Minute));		/* entrées */
	PORT_BUT &= ~((1<<B_Plus) | (1<<B_Minus) | (1<<B_Hour) | (1<<B_Minute));	/* sans pull-up */
}

void check_buttons()
{
	uint8_t brutStatus;
	uint8_t high_status;
	uint8_t low_status;

	pressed = 0;									/* réinitialisation */
	release = 0;

	brutStatus = ~PIN_BUT & 0b00111100;				/* prélève les status des touches */
													/* 1 : Bouton enfoncé */
													/* 0 : Bouton au repos */
													/* gestion du trigger & status trigger */
	high_status = 0x00; 							/* Boutons enfoncés */
	low_status = 0x00;								/* Boutons au repos */
	for (uint8_t i = 0; i < 4; ++i) {
		if (brutStatus & (1<<(i+2))) {
			if (trigger[i] < high_lvl)
				++trigger[i];
		} else {
			if (trigger[i] > 0)
				--trigger[i];
		}
		if (trigger[i] == high_lvl) {
			if (flood[i] < high_flood) {
				++flood[i];
			} else {
				flood[i] = high_flood * 0.66;
				pressed |= (1<<(i+2));
			}
			high_status |= (1<<(i+2));
		}
		if (trigger[i] == 0) {
			flood[i] = 0;
			low_status |= (1<<(i+2));
		}
	}												
	status1 = high_status | (~low_status & status);	/* status status1 pressed release */

	pressed |= status1 & ~status; 					/* bits passants de 0 -> 1 */
	release |= ~status1 & status; 					/* bits passants de 1 -> 0 */
	status = status1;
}
