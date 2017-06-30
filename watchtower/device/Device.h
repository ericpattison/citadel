#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "../../keep/types.h"
#include "../../watchtower/Color.h"

class Device {
public:
	Device(WindowInfo& info) {}
    virtual void Clear() = 0;
	virtual void Present() = 0;
	virtual void SetClearColor(const Color& color) = 0;
};

#endif