#include "OpenGLWindow.h"

#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include <stdio.h>

class OpenGLWindow::Impl {
public:
	Impl(WindowInfo& info) {
		printf("\n\tCreate Window OpenGL Linux Impl\n\n");
		display = XOpenDisplay(NULL);
		if(display == NULL) {
			printf("\n\tcannot connect to Xserver\n\n");
			exit(0);
		}

		root = DefaultRootWindow(display);

		GLint attributes[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		XVisualInfo* visualInfo = glXChooseVisual(display, 0, attributes);
		if(visualInfo == NULL) {
			printf("\n\tno appropriate visual found\n\n");
			exit(0);
		} else {
			printf("\n\tvisual %p selected\n", (void*)visualInfo->visualid);
		}
		colormap = XCreateColormap(display, root, visualInfo->visual, AllocNone);

		XSetWindowAttributes setWindowAttributes;
		setWindowAttributes.colormap = colormap;
		setWindowAttributes.event_mask = ExposureMask | KeyPressMask;

		windowHandle = XCreateWindow(display, root, 0, 0, 10, 10,
			0, visualInfo->depth, InputOutput, visualInfo->visual,
			CWColormap | CWEventMask, &setWindowAttributes);

		SetWindowSize(info.width, info.height);
		SetWindowTitle(info.title);

		XMapWindow(display, windowHandle);

		glContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
		glXMakeCurrent(display, windowHandle, glContext);
	}

	~Impl() {

	}

	void SetWindowTitle(String title) {
		std::string s(title.begin(), title.end());
		XStoreName(display, windowHandle, s.c_str());
	}

	void SetWindowSize(u32 width, u32 height) {
		XResizeWindow(display, windowHandle, width, height);
	}

	WindowStatus ProcessMessages() {
		XEvent xEvent;
		XNextEvent(display, &xEvent);
		switch (xEvent.type) {
		case Expose: {
			XWindowAttributes windowAttributes;
			XGetWindowAttributes(display, windowHandle, &windowAttributes);
			return WindowStatus::SystemUpdate;
		} break;

		case KeyPress: {
			return WindowStatus::Quit;
		} break;
		}

		return WindowStatus::GameUpdate;
	}

private:
	Display* display;
	Window root;
	Colormap colormap;
	Window windowHandle;
	GLXContext glContext;
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
