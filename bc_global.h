									/* Les Variables globales de BinaryClock */
#ifndef BC_GLOBAL_H
#define BC_GLOBAL_H


									/* uint8_t, uint16_t */
#include <inttypes.h>

									/* bc_variable */

extern uint8_t bc_time[3];			/* time { hour, minute, second } */
#define Hour	0
#define Minute	1
#define Second	2

extern uint8_t bc_prog;				/* actual program */
									/* numero du programme actuel
									  dépend de l'ordre dans lequel
									  il a été rajouté à bc_prog_list
									*/


class Program;
extern Program** bc_prog_list;		/* liste des Programmes */
extern uint8_t bc_size_list;

extern uint8_t bc_cregdiv[6];		/* tableau pour la gestion des couleurs dans bc_lreg.h et bc_display.h */

extern uint8_t bc_creg;				/* numero de la colonne actuel */

extern uint8_t bc_flags;			/* flags */
#define Flag_Clock		0
#define Flag_Forever	1
#define Flag_Sleep		2

extern uint8_t bc_cnums[6];			/* numero par colonnes */
									/* exemple : {1, 5, 2, 6, 0, 0} pour 15h26 */

extern int8_t bc_i;					/* pour les boucles for non compilées en -O3 */


#endif /* BC_GLOBAL_H */
