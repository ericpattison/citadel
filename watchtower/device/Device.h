#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "../../keep/types.h"
#include "../../watchtower/Color.h"
#include "../../keep/crypto/UUID.h"

class Device {
public:
    virtual void Clear() = 0;
	virtual void Present() = 0;
	virtual void SetClearColor(const Color& color) = 0;

	virtual UUID CreateRenderTarget(u32 w, u32 h, u32 d) = 0;

	virtual void BindResource(UUID uuid) = 0;
};

#endif
