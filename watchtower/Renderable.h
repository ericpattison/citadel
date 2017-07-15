#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include "../keep/types.h"

class Renderable {
public:
	virtual handle GetPlatformData() { return platformData; }
	virtual SetPlatformData(handle data) { platformData = data; }
private:
	handle platformData;
};

#endif