#ifndef BC_BUTTONS_H
#define BC_BUTTONS_H

#include <inttypes.h>

void init_buttons();
void check_buttons();

extern uint8_t status;
extern uint8_t pressed;
extern uint8_t release;

#endif /* BC_BUTTONS_H */
