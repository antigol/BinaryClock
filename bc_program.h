#ifndef BC_PROGRAM_H
#define BC_PROGRAM_H
#include <inttypes.h>

#include "bc_global.h"

class Program
{
public:
	Program();
	virtual void init(); // fonction d'initialisation
	virtual void uninit(); // fonction de desinitialisation
	virtual uint16_t run(); // fonction principale ( obligatoire )
	virtual uint16_t icon(); // fonction icon
	virtual void forever(); // fonction appelée en boucle dans le main
};

#endif

