#ifndef BC_REGISTERS_H
#define BC_REGISTERS_H
#include "bc_io.h"
#include <inttypes.h>

void init_registers();

/* C = (1<<_bitUp) */
void set_C_register(const uint8_t _bitUp);

/* C = 0 */
void clear_C_register();

/* 1 = ON, 0 = OFF
L = _data & 0x0FFF 
 { 0, 0, 0, 0, R8, R4, R2, R1, G8, G4, G2, G1, B8, B4, B2, B1 } */
void set_L_register(const uint16_t _data);

/* L = 0 */
void clear_L_register();

inline void tick_Clock()
{
	PORT_REG1 |= (1<<S_Clock);
	PORT_REG1 &= ~(1<<S_Clock);
}

inline void tick_C_Load()
{
	PORT_REG1 |= (1<<C_Load);
	PORT_REG1 &= ~(1<<C_Load);
}

inline void tick_L_Load()
{
	PORT_REG2 |= (1<<L_Load); // 1
	PORT_REG2 &= ~(1<<L_Load); // 0
}

inline void tick_Clear()
{
	PORT_REG2 &= ~(1<<S_Clear); // 0
	PORT_REG2 |= (1<<S_Clear); // 1
}


#endif /* BC_REGISTERS_H */
