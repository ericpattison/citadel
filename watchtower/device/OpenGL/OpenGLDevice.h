#ifndef _OPENGLDEVICE_H_
#define _OPENGLDEVICE_H_

#include "../Device.h"
#include "../../../keep/types.h"

class OpenGLDevice : public Device {
public:
	OpenGLDevice(WindowInfo& info);
	~OpenGLDevice();

    void Clear();
	void Present();
	void SetClearColor(const Color& color);

private:
	class Impl;
	SPtr<Impl> impl;
	WindowInfo windowInfo;
};

#endif
