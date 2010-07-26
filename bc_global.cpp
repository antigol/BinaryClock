#include "bc_global.h"
#include "bc_program.h"

uint8_t bc_time[3];
uint8_t bc_prog = 0;
Program **bc_prog_list;
uint8_t bc_size_list = 0;
uint8_t bc_cregdiv[6] = {0, 3, 5, 2, 4, 1};
uint8_t bc_creg = 0;
uint8_t bc_flags = 0;
uint8_t bc_cnums[6];
int8_t  bc_i;

