#ifndef _UTILS_ANDROID_H_
#define _UTILS_ANDROID_H_

#include <jni.h>
#include <android_native_app_glue.h>

#include "../../keep/window/SystemWindow.h"
struct AndroidWindowInfo : public WindowInfo {
	struct android_app* appState;
};

#endif