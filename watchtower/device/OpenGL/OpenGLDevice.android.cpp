#include "OpenGLDevice.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

#include "../../../keep/utils/android.h"

class OpenGLDevice::Impl {
public:
    Impl(WindowInfo& info) {
        windowInfo = (AndroidWindowInfo &) info;
        const EGLint attribs[] = {
            //EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
        };

        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        eglInitialize(display, 0, 0);
        eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);
        UPtr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
        eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);
        int i = 0;
        for(; i < numConfigs; ++i) {
            auto& cfg = supportedConfigs[i];
            EGLint r,g,b,d;
            if(eglGetConfigAttrib(display, cfg, EGL_RED_SIZE, &r) &&
                eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g) &&
                eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE, &b) &&
                eglGetConfigAttrib(display, cfg, EGL_DEPTH_SIZE, &d) &&
                r == 8 && g == 8 && b == 8 && d == 0) {

                config = supportedConfigs[i];
                break;
            }
        }
        if(i == numConfigs) {
            config = supportedConfigs[0];
        }

        eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

        ANativeWindow *window = windowInfo.appState->window;
        ANativeWindow_setBuffersGeometry(window, 0, 0, format);

        surface = eglCreateWindowSurface(display, config, window, nullptr);

        EGLint contextAttrs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttrs);

        EGLBoolean makeCurrent = eglMakeCurrent(display, surface, surface, context);

        eglQuerySurface(display, surface, EGL_WIDTH, &w);
        eglQuerySurface(display, surface, EGL_HEIGHT, &h);
        windowInfo.height = h;
        windowInfo.width = w;

        report();
        Initialize();
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
        //glDisable(GL_DITHER);
//        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
//        glEnable(GL_CULL_FACE);
//        glShadeModel(GL_SMOOTH);
//        glDisable(GL_DEPTH_TEST);

        glViewport(0, 0, w, h);
    }

    void report() {
        auto openglInfo = {GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS};
        for(auto name : openglInfo) {
            auto info = glGetString(name);
            LOGI("OpenGL Info: %s", info);
        }
    }

    EGLDisplay display;
    EGLSurface surface;
    EGLConfig config;
    EGLContext context;

    EGLint w, h, format;
    EGLint numConfigs;
    AndroidWindowInfo windowInfo;
};

OpenGLDevice::OpenGLDevice(WindowInfo& info) {
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