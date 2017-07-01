#include "OpenGLWindow.h"
#include "../../watchtower/device/OpenGL/OpenGLDevice.h"
#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include <stdio.h>

#include "../../keep/utils/linux.h"

class OpenGLWindow::Impl {
public:
	Impl(WindowInfo& info) {
		windowInfo = (LinuxWindowInfo&)info;
		printf("\n\tCreate Window OpenGL Linux Impl\n\n");
		windowInfo.display = XOpenDisplay(NULL);
		if(windowInfo.display == NULL) {
			printf("\n\tcannot connect to Xserver\n\n");
			exit(0);
		}

		root = DefaultRootWindow(windowInfo.display);

		GLint attributes[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		windowInfo.visualInfo = glXChooseVisual(windowInfo.display, 0, attributes);
		if(windowInfo.visualInfo == NULL) {
			printf("\n\tno appropriate visual found\n\n");
			exit(0);
		} else {
			printf("\n\tvisual %p selected\n", (void*)windowInfo.visualInfo->visualid);
		}
		colormap = XCreateColormap(windowInfo.display, root, windowInfo.visualInfo->visual, AllocNone);

		XSetWindowAttributes setWindowAttributes;
		setWindowAttributes.colormap = colormap;
		setWindowAttributes.event_mask = ExposureMask | KeyPressMask;

		windowInfo.windowHandle = XCreateWindow(windowInfo.display, root, 0, 0, 10, 10,
			0, windowInfo.visualInfo->depth, InputOutput, windowInfo.visualInfo->visual,
			CWColormap | CWEventMask, &setWindowAttributes);

		SetWindowSize(info.width, info.height);
		SetWindowTitle(info.title);

		XMapWindow(windowInfo.display, windowInfo.windowHandle);

		//glContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
		//glXMakeCurrent(display, windowHandle, glContext);
	}

	~Impl() {

	}

	void SetWindowTitle(String title) {
		std::string s(title.begin(), title.end());
		XStoreName(windowInfo.display, windowInfo.windowHandle, s.c_str());
	}

	void SetWindowSize(u32 width, u32 height) {
		windowInfo.width = width;
		windowInfo.height = height;
		XResizeWindow(windowInfo.display, windowInfo.windowHandle, windowInfo.width, windowInfo.height);
	}

	WindowStatus ProcessMessages() {
		XEvent xEvent;
		XNextEvent(windowInfo.display, &xEvent);
		switch (xEvent.type) {
		case Expose: {
			XWindowAttributes windowAttributes;
			XGetWindowAttributes(windowInfo.display, windowInfo.windowHandle, &windowAttributes);
			return WindowStatus::SystemUpdate;
		} break;

		case KeyPress: {
			return WindowStatus::Quit;
		} break;
		}

		return WindowStatus::GameUpdate;
	}

	LinuxWindowInfo& GetWindowInfo() {
		return windowInfo;
	}

private:
	Window root;
	Colormap colormap;
	LinuxWindowInfo windowInfo;
};

OpenGLWindow::OpenGLWindow(WindowInfo& info) : SystemWindow(info) {
	impl = MakeUPtr<Impl>(info);
}

OpenGLWindow::~OpenGLWindow() {

}

void OpenGLWindow::Resize(u32 width, u32 height) {
	impl->SetWindowSize(width, height);
}

void OpenGLWindow::Title(String title) {
	impl->SetWindowTitle(title);
}

WindowStatus OpenGLWindow::ProcessMessages() {
	return impl->ProcessMessages();
}

void OpenGLWindow::Exit(int errorCode) {

}

SPtr<Device> OpenGLWindow::AcquireDevice() {
	return MakeSPtr<OpenGLDevice>(impl->GetWindowInfo());
}
