#include "OpenGLWindow.h"
#include "keep/types.h"
#include "../../keep/constants.h"
#include "../../keep/utils/android.h"
#include "../../watchtower/device/OpenGL/OpenGLDevice.h"

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__))


class OpenGLWindow::Impl {
public:
	Impl(WindowInfo& info) {
        windowInfo = (AndroidWindowInfo&)info;
        appState = windowInfo.appState;

	}

	WindowStatus ProcessMessages() {
		int events;
		struct android_poll_source* source;
		int ident = ALooper_pollAll(0, 0, &events, (void**)&source);
		if (ident >= 0) {
			if (appState->destroyRequested) { return WindowStatus::Quit; }
			if (source) {
				source->process(appState, source);
				return WindowStatus::SystemUpdate;
			}
		}

		return WindowStatus::GameUpdate;
	}

    AndroidWindowInfo& getWindowInfo() { return windowInfo; }

private:
	android_app* appState;
    AndroidWindowInfo windowInfo;
};

OpenGLWindow::OpenGLWindow(WindowInfo& info) : SystemWindow(info) {
    impl = MakeUPtr<OpenGLWindow::Impl>(info);
}

OpenGLWindow::~OpenGLWindow() { }

void OpenGLWindow::Resize(u32 width, u32 height) {}

void OpenGLWindow::Title(String title) {

}

WindowStatus OpenGLWindow::ProcessMessages() {
	return impl->ProcessMessages();
}

void OpenGLWindow::Exit(int errorCode) { }

SPtr<Device> OpenGLWindow::AcquireDevice() {
	return MakeSPtr<OpenGLDevice>(impl->getWindowInfo());
}