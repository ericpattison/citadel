#ifndef _UTILS_LINUX_H_
#define _UTILS_LINUX_H_

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

#include "../../keep/window/SystemWindow.h"
struct LinuxWindowInfo : WindowInfo {
	Window windowHandle;
	Display* display;
	XVisualInfo* visualInfo;
};

#endif