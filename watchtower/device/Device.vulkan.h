#ifndef _DEVICEVULKAN_H_
#define _DEVICEVULKAN_H_

#include "Device.h"
#include <memory>

class DeviceVulkan : public Device {
public:
	DeviceVulkan();
	~DeviceVulkan();

	virtual void Initialize();
	virtual void Shutdown();

private:
	class Impl;
	std::shared_ptr<Impl> impl;
};

#endif