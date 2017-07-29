#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "../../keep/types.h"

class Renderer {
public:
	virtual Callback RenderMethod() = 0;
};

#endif