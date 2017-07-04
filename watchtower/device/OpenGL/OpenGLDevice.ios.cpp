#include "OpenGLDevice.h"

#include <OpenGLES/ES3/gl.h>

class OpenGLDevice::Impl {
public:
    
    void Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void Present() {
        
    }
    
    void SetClearColor(const Color& color) {
        glClearColor(color.r(), color.g(), color.b(), color.a());
    }
    
private:
};

OpenGLDevice::OpenGLDevice(WindowInfo& info) {
    impl = MakeSPtr<Impl>();
}

OpenGLDevice::OpenGLDevice(OpenGLDevice&& other) {
    this->impl = other.impl;
}

OpenGLDevice::~OpenGLDevice() {
    
}

void OpenGLDevice::Clear() {
    impl->Clear();
}

void OpenGLDevice::Present() {
    impl->Present();
}

void OpenGLDevice::SetClearColor(const Color &color) {
    impl->SetClearColor(color);
}
