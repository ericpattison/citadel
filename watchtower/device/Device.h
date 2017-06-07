#ifndef _DEVICE_H_
#define _DEVICE_H_

class Device {
public:
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
};

#endif