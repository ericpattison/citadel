#include "Window.h"
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

class Window::Impl {
public:
	void Create(WindowInfo info) {
		WNDCLASSEX wcex = { 0 };
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WindowProc;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszClassName = L"CitadelWindowClass";
		
		if (!RegisterClassEx(&wcex)) {
			throw std::runtime_error("Failed to register Window");
		}

		RECT rect = { 0, 0, (s32)info.width, (s32)info.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		const int windowWidth = (rect.right - rect.left);
		const int windowHeight = (rect.bottom - rect.top);

		HWND hwnd = CreateWindowEx(0, wcex.lpszClassName, (LPCWSTR)info.title.c_str(),
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, windowWidth, windowHeight,
			nullptr, nullptr, nullptr, nullptr);

		if (!hwnd) {
			throw std::runtime_error("Failed to create Window");
		}

		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);

		windowHandle = hwnd;
	}

	void Resize(u32 width, u32 height) {
		RECT rect = { 0, 0, (s32)width, (s32)height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
		const int windowWidth = (rect.right - rect.left);
		const int windowHeight = (rect.bottom - rect.top);

		RECT windowRect;
		GetWindowRect(windowHandle, &windowRect);
		MoveWindow(
			windowHandle,
			windowRect.left, windowRect.top,
			windowWidth, windowHeight,
			TRUE
		);
	}

	void Title(String title) {
		SetWindowTextA(windowHandle, title.c_str());
	}

	WindowStatus ProcessMessages() {
		MSG message;
		BOOL hasMessage = PeekMessage(&message, NULL, 0, 0, PM_REMOVE);
		if (!hasMessage) return WindowStatus::GameUpdate;

		TranslateMessage(&message);
		DispatchMessage(&message);
		if (message.message == WM_QUIT) return WindowStatus::Quit;

		return WindowStatus::SystemUpdate;
	}

	void Exit(int errorCode) {
		ExitProcess(errorCode);
	}
private:
	HWND windowHandle;
};

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

Window::Window(WindowInfo info): impl(std::make_unique<Impl>()) {
	FreeConsole();
	impl->Create(info);
}

Window::~Window() {
}

void Window::Resize(u32 width, u32 height) {
	impl->Resize(width, height);
}

void Window::Title(String title) {
	impl->Title(title);
}

WindowStatus Window::ProcessMessages() {
	return impl->ProcessMessages();
}

void Window::Exit(int errorCode) {
	impl->Exit(errorCode);
}