#include "OpenGLDevice.h"

#include <GLES/gl.h>
#include <GLES3/gl32.h>
#include <EGL/egl.h>

#include "../../../keep/utils/android.h"

class OpenGLDevice::Impl {
public:
    Impl(WindowInfo& info) {
        windowInfo = (AndroidWindowInfo &) info;
        const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
        };

        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        eglInitialize(display, 0, 0);
        eglChooseConfig(display, attribs, &config, 1, &numConfigs);
        eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

        ANativeWindow *window = windowInfo.appState->window;
        ANativeWindow_setBuffersGeometry(window, 0, 0, format);

        surface = eglCreateWindowSurface(display, config, window, nullptr);
        context = eglCreateContext(display, config, nullptr, nullptr);

        EGLBoolean makeCurrent = eglMakeCurrent(display, surface, surface, context);

        eglQuerySurface(display, surface, EGL_WIDTH, &w);
        eglQuerySurface(display, surface, EGL_HEIGHT, &h);
        windowInfo.height = h;
        windowInfo.width = w;

        glViewport(0, 0, w, h);
    }

    void Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Present() {
        eglSwapBuffers(display, surface);
    }

	void SetClearColor(const Color& color) {
		glClearColor(color.r(), color.g(), color.b(), color.a());
	}

private:
    void Initialize() {
        glDisable(GL_DITHER);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
        glEnable(GL_CULL_FACE);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        glViewport(0, 0, w, h);
        GLfloat ratio = (GLfloat)w / (GLfloat)h;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustumf(-ratio, ratio, -1, 1, 1, 10);
    }

    EGLDisplay display;
    EGLSurface surface;
    EGLConfig config;
    EGLContext context;

    EGLint w, h, format;
    EGLint numConfigs;
    AndroidWindowInfo windowInfo;
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