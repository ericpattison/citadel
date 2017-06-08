#include "Window.h"

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#include <memory>


class Window::Impl {
public:
	void CreateWindow(WindowInfo info) {
		display = XOpenDisplay(NULL);
		root = DefaultRootWindow(display);

		GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		visual = glXChooseVisual(display, 0, att);

		colormap = XCreateColormap(display, root, vi->visual, AllocNone);

		setWindowAttributes.colormap = colormap;
		setWindowAttributes.event_mask = ExposureMask | KeyPressMask;

		windowHandle = XCreateWindow(display, root, 0, 0, info.width, info.height, 0, vi->depth, InputOutput, vi->visual, CWColorMap | CWEventMask, 
&setWindowAttributes);

		XMapWindow(display, windowHandle);
		XStoreName(display, windowHandle, info.title.c_str());
	}

	WindowStatus ProcessMessages() {
		XNextEvent(display, &event);
		if(event.type == Expose) {
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
}

Window::Window(WindowInfo info) : impl(std::make_unique<IMPL>()) {
	impl->CreateWindow(info);
}

Window::~Window() {
}

void Window:Resize(u32 width, u32 height) { }

void Window:Title(String title) {
}

WindowStatus Window::ProcessMessages() {
}

void Window::Exit(int errorCode) {
	exit(errorCode);
}

