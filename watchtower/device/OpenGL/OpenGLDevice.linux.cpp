#include "OpenGLDevice.h"
#include "../../../keep/utils/linux.h"
#include <GL/gl.h>

class OpenGLDevice::Impl {
public:
	Impl(WindowInfo& info) {
		windowInfo = (LinuxWindowInfo&)info;
		context = glXCreateContext(windowInfo.display, windowInfo.visualInfo, NULL, GL_TRUE);
		glXMakeCurrent(windowInfo.display, windowInfo.windowHandle, context);
	}

	~Impl() { }

	void Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Present() {
		glXSwapBuffers(windowInfo.display, windowInfo.windowHandle);
	}

	void SetClearColor(const Color& color) {
		glClearColor(color.r(), color.g(), color.b(), color.a());
	}

private:
	LinuxWindowInfo windowInfo;
	GLXContext context;	
};

OpenGLDevice::OpenGLDevice(WindowInfo& windowInfo) : Device(windowInfo) {
	impl = MakeUPtr<Impl>(windowInfo);
}

OpenGLDevice::~OpenGLDevice() {
}

void OpenGLDevice::Clear() {
	impl->Clear();
}

void OpenGLDevice::Present() {
	impl->Present();
}

void OpenGLDevice::SetClearColor(const Color& color) {
	impl->SetClearColor(color);
}
