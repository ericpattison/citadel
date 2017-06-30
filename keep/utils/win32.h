#ifndef _UTILS_WIN32_H_
#define _UTILS_WIN32_H_

#include <Windows.h>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

#include "../../keep/window/SystemWindow.h"
struct Win32WindowInfo : WindowInfo	{
	HWND hwnd;
};

#endif