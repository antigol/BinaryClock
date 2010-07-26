#include "bc_program.h"
#include "bc_lreg.h"

Program::Program()
{
	bc_prog_list[bc_size_list] = this;
	++bc_size_list;
}

void Program::init()
{
}

void Program::uninit()
{
}

uint16_t Program::run()
{
	return 0x80;
}

uint16_t Program::icon()
{
	uint8_t num = bc_prog;
	switch (bc_creg) {
		case 4: num /= 10; break;
		case 5: num %= 10; break;
		default: num = 0;
	}

	Lreg lreg;
	lreg.addLeds(num, BC::white);
	return lreg.value();
}

void Program::forever()
{
}
