#include "OpenGLWindow.h"
#include "../../watchtower/device/OpenGL/OpenGLDevice.h"

class OpenGLWindow::Impl {
public:
    Impl(WindowInfo info) {
        windowInfo = info;
    }
    WindowInfo& getWindowInfo() { return windowInfo; }
private:
    WindowInfo windowInfo;
};

OpenGLWindow::OpenGLWindow(WindowInfo& info) : SystemWindow(info) {
    impl = MakeUPtr<Impl>(info);
}

OpenGLWindow::~OpenGLWindow() {
    
}

void OpenGLWindow::Resize(u32 width, u32 height) {

}

void OpenGLWindow::Title(String title) {

}

WindowStatus OpenGLWindow::ProcessMessages() {
    return WindowStatus::GameUpdate;
}

void OpenGLWindow::Exit(int errorCode) { }

SPtr<Device> OpenGLWindow::AcquireDevice() {
    return MakeSPtr<OpenGLDevice>(impl->getWindowInfo());
}
