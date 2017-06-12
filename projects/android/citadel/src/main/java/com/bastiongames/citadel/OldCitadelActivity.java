package com.bastiongames.citadel;

import android.app.Activity;
import android.os.Bundle;
import android.view.Surface;

public class OldCitadelActivity extends Activity {

    static {
        System.loadLibrary("citadel");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    public static native void OnCreateNative();

    public static native void SetSurface( Surface surface );

    public static native void SetSurfaceSize( int width, int height );

    public static native void DrawFrame();
}
