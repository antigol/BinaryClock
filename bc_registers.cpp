#include "bc_registers.h"

void init_registers()
{
	DDR_REG1 |= (1<<S_Clock) | (1<<C_Load);
	DDR_REG2 |= (1<<L_Load) | (1<<S_Clear) | (1<<S_Data);

	PORT_REG1 &= ~(1<<S_Clock);
	PORT_REG1 &= ~(1<<C_Load);

	PORT_REG2 &= ~(1<<L_Load);
	PORT_REG2 |= (1<<S_Clear);
	PORT_REG2 &= ~(1<<S_Data);
}

/*	0 H10
	1 H1
	2 M10
	3 M1
	4 S10
	5 S1*/
void set_C_register(const uint8_t _bitUp)
{
	tick_Clear();
	PORT_REG2 |= (1<<S_Data);
	tick_Clock();
	PORT_REG2 &= ~(1<<S_Data);
	for (uint8_t i = 0; i < _bitUp + 2; ++i)
		tick_Clock();
	tick_C_Load();
}

void clear_C_register()
{
	tick_Clear();
	tick_C_Load();
}

void set_L_register(const uint16_t _data)
{
	// la boucle est automatiquement deroulée
	for (int8_t i = 11; i >= 0; --i) {
		if (_data & (1<<i))
			PORT_REG2 |= (1<<S_Data);
		else
			PORT_REG2 &= ~(1<<S_Data);
		tick_Clock();
	}
	tick_L_Load();
}

void clear_L_register()
{
	tick_Clear();
	tick_L_Load();
}

