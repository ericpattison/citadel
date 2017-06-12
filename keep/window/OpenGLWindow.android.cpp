#include "OpenGLWindow.h"
#include "keep/types.h"
#include "../../keep/constants.h"
#include "../../keep/utils/android.h"
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__))


class OpenGLWindow::Impl {
public:
	Impl(WindowInfo& info) {
		appState = ((AndroidWindowInfo&)info).appState;
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

private:
	android_app* appState;
};

OpenGLWindow::OpenGLWindow(WindowInfo& info) : SystemWindow(info) {
	impl = MakeUPtr<OpenGLWindow::Impl>(info);
}

OpenGLWindow::~OpenGLWindow() { }

void OpenGLWindow::Resize(u32 width, u32 height) {}

void OpenGLWindow::Title(String title) {

}

WindowStatus OpenGLWindow::ProcessMessages() {
	LOGI("Processing System Messages!");
	return impl->ProcessMessages();
}

void OpenGLWindow::Exit(int errorCode) { }
