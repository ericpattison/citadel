#ifndef _COLOR_H_
#define _COLOR_H_

#include "../keep/types.h"

class Color {
public:
	Color(u8 r, u8 g, u8 b, u8 a) {
		_r = r / 255.f;
		_g = g / 255.f;
		_b = b / 255.f;
		_a = a / 255.f;
	}

	/*Color(real r, real g, real b, real a) {
		_r = r;
		_g = g;
		_b = b;
		_a = a;
	}*/

	real r()const { return _r; }
	real g()const { return _g; }
	real b()const { return _b; }
	real a()const { return _a; }

private:
	real _r, _g, _b, _a;
};

#endif