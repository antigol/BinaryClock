#ifndef BC_COLOR_H
#define BC_COLOR_H

#include <inttypes.h>

typedef uint16_t BCrgb;
// 0b0rrr rrgg gggb bbbb
// 0b    '    '    '

inline uint8_t red(BCrgb rgb)
{ return ((rgb >> 10) & 0x1F); }

inline uint8_t green(BCrgb rgb)
{ return ((rgb >> 5) & 0x1F); }

inline uint8_t blue(BCrgb rgb)
{ return (rgb & 0x1F); }


inline BCrgb bc_rgb(uint8_t r, uint8_t g, uint8_t b)// set RGB value
{ return ((r & 0x1F) << 10) | ((g & 0x1F) << 5) | (b & 0x1F); }

// Teinte - lumière vers Red green blue ( saturation = 100% )
// t[0;185] + l[0;31]  to rgb {0-31, 0-31, 0-31}
// l = 0 -> couleur normale
// l > 0 -> couleur mélangée avec du blanc
// ATTENTION : dure >300 us !
BCrgb bc_tsl(uint8_t t, uint8_t l = 0);

namespace BC {
	enum {
		red = 0x7C00, 
		green = 0x03E0, 
		blue = 0x001F, 
		white = 0x7FFF,
		cyan = 0x03FF,
		magenta = 0x7C1F,
		yellow = 0x7FE0,
	};
}

#endif /* BC_COLOR_H */
