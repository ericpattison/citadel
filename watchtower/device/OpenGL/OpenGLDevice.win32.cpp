#include "OpenGLDevice.h"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "../../../keep/utils/win32.h"

class OpenGLDevice::Impl {
public:
	Impl(WindowInfo& info) {
		Win32WindowInfo windowInfo = (Win32WindowInfo&)info;
		
		hwnd = windowInfo.hwnd;
		hdc = GetDC(windowInfo.hwnd);

		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.cColorBits = 32;
		pfd.iPixelType = PFD_TYPE_RGBA;

		int pf = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, pf, &pfd);
		DescribePixelFormat(hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		hrc = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hrc);

		glViewport(0, 0, windowInfo.width, windowInfo.height);
	}

	~Impl() {
		wglMakeCurrent(nullptr, nullptr);
		ReleaseDC(hwnd, hdc);
		wglDeleteContext(hrc);
	}

	void Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Present() {
		//glFlush();
		SwapBuffers(hdc);
	}

	void SetClearColor(const Color& color) {
		glClearColor(color.r(), color.g(), color.b(), color.a());
	}

private:
	HDC hdc;
	HGLRC hrc;
	HWND hwnd;
};

OpenGLDevice::OpenGLDevice(WindowInfo& info) : Device(info) {
	impl = MakeUPtr<Impl>(info);
}

OpenGLDevice::~OpenGLDevice() {

}

void OpenGLDevice::Clear() {
	impl->Clear();
}

void OpenGLDevice::Present() {
	impl->Present();
}

void OpenGLDevice::SetClearColor(const Color& color) {
	impl->SetClearColor(color);
}