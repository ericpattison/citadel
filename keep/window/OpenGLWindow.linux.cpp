#include "OpenGLWindow.h"

#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

class OpenGLWindow::Impl {
public:
	Impl(WindowInfo info) {
		display = XOpenDisplay(NULL);
		root = DefaultRootWindow(display);

		GLint attributes[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		XVisualInfo* visualInfo = glXChooseVisual(display, 0, attributes);

		XSetWindowAttributes setWindowAttributes;
		setWindowAttributes.colormap = colormap;
		setWindowAttributes.event_mask = ExposureMask | KeyPressMask;
		colormap = XCreateColormap(display, root, visualInfo->visual, AllocNone);

		windowHandle = XCreateWindow(display, root, 0, 0, 10, 10,
			0, visualInfo->depth, InputOutput, visualInfo->visual,
			CWColormap | CWEventMask, &setWindowAttributes);

		SetWindowSize(info.width, info.height);
		SetWindowTitle(info.title);

		XMapWindow(display, windowHandle);

		glContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
		glXMakeCurrent(display, windowHandle, context);
	}

	~Impl() {

	}

	void SetWIndowTitle(String title) {
		XStoreName(display, windowHandle, title.c_str());
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

OpenGLWindow::OpenGLWindow(WindowInfo info) : SystemWindow(info) {
	impl = MakeUPtr<Impl>(info);
}

OpenGLWindow::~OpenGLWindow() {

}

void OpenGLWindow::Resize(u32 width, u32 height) {
	impl->SetWindowSize(width, height);
}

void OpenGLWindow::Title(String title) {
	impl->SetWIndowTitle(title);
}

WindowStatus OpenGLWindow::ProcessMessages() {
	return impl->ProcessMessages();
}

void OpenGLWindow::Exit(int errorCode) {

}