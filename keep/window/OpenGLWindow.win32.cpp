#include "OpenGLWindow.h"
#include "../utils/win32.h"

#include "../../watchtower/device/OpenGL/OpenGLDevice.h"

#include "../../keep/utils/win32.h"

class OpenGLWindow::Impl {
public:
	Impl(WindowInfo& info) {
		windowInfo = (Win32WindowInfo&)info;

		WNDCLASSEX wcex = { 0 };
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.lpfnWndProc = WindowProc;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszClassName = L"CitadelWindowClass";

		if (!RegisterClassEx(&wcex)) {
			throw std::runtime_error("Failed to register Window class");
		}

		RECT rect = { 0, 0, (s32)windowInfo.width, (s32)windowInfo.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
		const int windowWidth = (rect.right - rect.left);
		const int windowHeight = (rect.bottom - rect.top);

		HWND hwnd = CreateWindowEx(0, wcex.lpszClassName, (LPCWSTR)windowInfo.title.c_str(),
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, windowWidth, windowHeight,
			nullptr, nullptr, nullptr, nullptr);

		if (!hwnd) {
			throw std::runtime_error("Failed to create window");
		}

		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);

		windowHandle = hwnd;
		windowInfo.hwnd = hwnd;
	}

	void SetWindowSize(u32 width, u32 height) {
		RECT rect = { 0,0,(s32)width,(s32)height };
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

	void SetWindowTitle(String title) {
		SetWindowText(windowHandle, title.c_str());
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

	Win32WindowInfo& getWindowInfo() { return windowInfo; }

	void Invalidate() {
		RECT r{ 0,0,1280,720 };
		InvalidateRect(windowHandle, &r, true);
	}

private:
	Win32WindowInfo windowInfo;
	HWND windowHandle;
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

void OpenGLWindow::Exit(int errorCode) {}

SPtr<Device> OpenGLWindow::AcquireDevice() {
	auto device = MakeSPtr<OpenGLDevice>(impl->getWindowInfo());
	impl->Invalidate();
	return device;
}