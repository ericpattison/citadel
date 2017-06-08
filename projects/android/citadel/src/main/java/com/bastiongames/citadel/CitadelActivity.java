package com.bastiongames.citadel;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.view.MotionEvent;
import android.view.Surface;

public class CitadelActivity extends Activity {
    protected static GLView mainView = null;

    static {
        System.loadLibrary("citadel-lib");
    }

    @Override
    protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);

        SetAPKName(getApplication().getApplicationInfo().sourceDir);

        String storagePrefix = GetStoragePrefix();

        OnCreateNative(storagePrefix);
        mainView = new GLView(getApplication());
        setContentView(mainView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        ExitNative();
    }

    protected static boolean ProtessTouchEvent(MotionEvent event) {
        SendMotion(-1, 0, 0, false, MOTION_MOVE);

        int E = event.getAction() & MotionEvent.ACTION_MASK;
        int index = event.getActionIndex();
        int pointerID = event.getPointerId((event.getAction()&MotionEvent.ACTION_POINTER_INDEX_MASK)>>MotionEvent.ACTION_POINTER_INDEX_SHIFT);

        try {
            int x = (int)event.getX();
            int y = (int)event.getY();

            if(E == MotionEvent.ACTION_DOWN) {
                for(int i = 0; i != event.getPointerCount(); ++i) {
                    SendMotion(event.getPointerId(i), (int)event.getX(i), (int)event.getY(i), true, MOTION_DOWN);
                }
            }

            if(E == MotionEvent.ACTION_UP || E == MotionEvent.ACTION_CANCEL) {
                SendMotion(-2, 0, 0, false, MOTION_UP);
                return E <= MotionEvent.ACTION_MOVE;
            }

            int maskedEvent = event.getActionMasked();
            if(maskedEvent == MotionEvent.ACTION_POINTER_DOWN) {
                for(int i = 0; i != event.getPointerCount(); ++i) {
                    SendMotion(event.getPointerId(i), (int)event.getX(i), (int)event.getY(i), true, MOTION_DOWN);
                }
            }

            if(maskedEvent == MotionEvent.ACTION_POINTER_UP) {
                for(int i = 0; i != event.getPointerCount(); ++i) {
                    SendMotion(event.getPointerId(i), (int)event.getX(i), (int)event.getY(i), i != pointerID, MOTION_UP);
                }
                SendMotion(pointerID, (int)event.getX(pointerID), (int)event.getY(pointerID), false, MOTION_MOVE);
            }

            if(maskedEvent == MotionEvent.ACTION_MOVE) {
                for(int i = 0; i != event.getPointerCount(); ++i) {
                    SendMotion(event.getPointerId(i), (int)event.getX(i), (int)event.getY(i), true, MOTION_MOVE);
                }
            }
        } catch(java.lang.IllegalArgumentException ex) { }

        SendMotion(-2, 0, 0, false, MOTION_MOVE);
        return E <= MotionEvent.ACTION_MOVE;
    }

    protected String GetStoragePrefix() {
        String state = Environment.getExternalStorageState();
        if(!Environment.MEDIA_MOUNTED.equals(state) || Environment.MEDIA_MOUNTED_READ_ONLY.equals(state)) {
            return this.getDir(getApplication().getPackageName(), MODE_PRIVATE).getPath();
        }
        return Environment.getExternalStorageDirectory().getPath() + "/external_sd/Android/data/" + getApplication().getPackageName();
    }

    private static final int MOTION_MOVE = 0;
    private static final int MOTION_UP = 1;
    private static final int MOTION_DOWN = 2;

    private static final int MOTION_START = -1;
    private static final int MOTION_END = -2;

    private static final int LBUTTON = 1;

    public static native void OnCreateNative(String storage);
    public static native void SetSurface(Surface surface);
    public static native void SetSurfaceSize(int width, int height);
    public static native void DrawFrame();
    public static native void SetAPKName(String apkName);
    public static native void ExitNative();
    public static native void SendMotion(int pointerId, int x, int y, boolean pressed, int flag);
}
