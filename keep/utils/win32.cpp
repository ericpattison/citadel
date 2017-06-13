#include "win32.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	switch (message) {
	case WM_KEYDOWN: {
		if (wparam == VK_ESCAPE) {
			PostMessage(hwnd, WM_DESTROY, 0, 0);
			return 0;
		}
	}break;

	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}break;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}