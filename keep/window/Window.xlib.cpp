#include "Window.h"

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include <memory>


class SystemWindow::Impl {
public:

	void CreateWindow(WindowInfo info) {
		display = XOpenDisplay(NULL);
		root = DefaultRootWindow(display);

		GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		XVisualInfo *visualInfo = glXChooseVisual(display, 0, att);

		colormap = XCreateColormap(display, root, visualInfo->visual, AllocNone);

		setWindowAttributes.colormap = colormap;
		setWindowAttributes.event_mask = ExposureMask | KeyPressMask;

		windowHandle = XCreateWindow(display, root, 0, 0, info.width, info.height, 0, visualInfo->depth, InputOutput, visualInfo->visual, CWColormap | 
CWEventMask, &setWindowAttributes);

		XMapWindow(display, windowHandle);
		XStoreName(display, windowHandle, info.title.c_str());

		context = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
		glXMakeCurrent(display, windowHandle, context);
	}

	WindowStatus ProcessMessages() {
		XNextEvent(display, &event);
		if(event.type == Expose) {
			XGetWindowAttributes(display, windowHandle, &windowAttributes);
			glViewport(0, 0, windowAttributes.width, 
windowAttributes.height);

			glClearColor(1.0, 1.0, 1.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1,1,-1,1,1,20);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(0,0,10,0,0,0,0,1,0);

			glBegin(GL_QUADS);
				glColor3f(1,0,0); glVertex3f(-.75, -.75, 0);
				glColor3f(0,1,0); glVertex3f(.75, -.75, 0);
				glColor3f(0,0,1); glVertex3f(.75, .75, 0);
				glColor3f(1,1,0); glVertex3f(-.75, .75, 0);
			glEnd();

			glXSwapBuffers(display, windowHandle);

			return WindowStatus::SystemUpdate;
		}
		else if(event.type == KeyPress) {
			return WindowStatus::Quit;
		}
		return WindowStatus::GameUpdate;
	}
private:
	Display* display;
	Window root;
	Colormap colormap;
	XSetWindowAttributes setWindowAttributes;
	Window windowHandle;
	XWindowAttributes windowAttributes;
	XEvent event;
	GLXContext context;
};

SystemWindow::SystemWindow(WindowInfo info) : impl(std::make_unique<Impl>()) {
	impl->CreateWindow(info);
}

SystemWindow::~SystemWindow() {
}

void SystemWindow::Resize(u32 width, u32 height) { }

void SystemWindow::Title(String title) {
}

WindowStatus SystemWindow::ProcessMessages() {
	return impl->ProcessMessages();
}

void SystemWindow::Exit(int errorCode) {
	exit(errorCode);
}

