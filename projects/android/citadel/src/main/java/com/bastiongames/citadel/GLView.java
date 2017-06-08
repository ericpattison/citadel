package com.bastiongames.citadel;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

public class GLView extends GLSurfaceView {
    private static final String TAG = "GLView";

    public GLView(Context context) {
        super(context);
        init(16,0);
    }

    private void init(int depth, int stencil) {
        this.getHolder().setFormat(PixelFormat.RGB_888);
        setEGLContextFactory(new ContextFactory());
        setEGLConfigChooser(new ConfigChooser(8, 8, 8, 0, depth, stencil));
        setRenderer(new Renderer());
    }

    private static void checkEglError(String prompt, EGL10 egl) {
        int error;
        while((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) {
            Log.e(TAG, String.format("%s: EGL Error: 0x%x", prompt, error));
        }
    }

    private static class ContextFactory implements GLSurfaceView.EGLContextFactory {
        private static final int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

        public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig config) {
            Log.i(TAG, "creating OpenGL ES 2.0 context");
            checkEglError("before eglCreateContext", egl);
            int[] attribList = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE};
            EGLContext context = egl.eglCreateContext(display, config, EGL10.EGL_NO_CONTEXT, attribList);
            checkEglError("after eglCreateContext", egl);
            return context;
        }

        public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
            egl.eglDestroyContext(display, context);
        }
    }

    private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser {
        protected int mRedSize, mGreenSize, mBlueSize, mAlphaSize;
        protected int mDepthSize, mStencilSize;
        private int[] mValue = new int[1];

        private static final int EGL_OPENGL_ES2_BIT = 4;
        private static final int[] CONFIG_ATTRIBS = {
                EGL10.EGL_RED_SIZE, 5,
                EGL10.EGL_GREEN_SIZE, 6,
                EGL10.EGL_BLUE_SIZE, 5,
                EGL10.EGL_ALPHA_SIZE, 0,
                EGL10.EGL_DEPTH_SIZE, 16,
                EGL10.EGL_STENCIL_SIZE, 0,
                EGL10.EGL_SAMPLE_BUFFERS, 0,
                EGL10.EGL_SAMPLES, 0,
                EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                EGL10.EGL_NONE, EGL10.EGL_NONE
        };

        public ConfigChooser(int r, int g, int b, int a, int depth, int stencil) {
            mRedSize = r;
            mGreenSize = g;
            mBlueSize = b;
            mAlphaSize = a;
            mDepthSize = depth;
            mStencilSize = stencil;
        }

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {
            int[] numConfig = new int[1];
            egl.eglChooseConfig(display, CONFIG_ATTRIBS, null, 0, numConfig);
            int numConfigs = numConfig[0];
            if(numConfigs <= 0) {
                throw new IllegalArgumentException("No configs match configSpec");
            }
            EGLConfig[] configs = new EGLConfig[numConfigs];
            egl.eglChooseConfig(display, CONFIG_ATTRIBS, configs, numConfigs, numConfig);
            return chooseConfig(egl, display, configs);
        }

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display, EGLConfig[] configs) {
            for(EGLConfig config : configs) {
                int d = findConfigAttrib(egl, display, config, EGL10.EGL_DEPTH_SIZE, 0);
                int s = findConfigAttrib(egl, display, config, EGL10.EGL_STENCIL_SIZE, 0);
                if( d < mDepthSize || s < mStencilSize) {
                    continue;
                }

                int r = findConfigAttrib(egl, display, config, EGL10.EGL_RED_SIZE, 0);
                int g = findConfigAttrib(egl, display, config, EGL10.EGL_GREEN_SIZE, 0);
                int b = findConfigAttrib(egl, display, config, EGL10.EGL_BLUE_SIZE, 0);
                int a = findConfigAttrib(egl, display, config, EGL10.EGL_ALPHA_SIZE, 0);

                if(r == mRedSize && g == mGreenSize && b == mBlueSize && a == mAlphaSize){
                    return config;
                }
            }
            return null;
        }

        private int findConfigAttrib(EGL10 egl, EGLDisplay display, EGLConfig config, int attribute, int defaultValue) {
            if(egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
                return mValue[0];
            }
            return defaultValue;
        }
    }

    private static class Renderer implements GLSurfaceView.Renderer {
        public void onDrawFrame(GL10 gl) {
            CitadelActivity.DrawFrame();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            CitadelActivity.SetSurfaceSize(width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            CitadelActivity.SetSurface(CitadelActivity.mainView.getHolder().getSurface());
        }
    }
}
