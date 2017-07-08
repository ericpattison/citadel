#ifndef _UTILS_ANDROID_H_
#define _UTILS_ANDROID_H_

#include <jni.h>
#include <android_native_app_glue.h>

#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

#include "../../keep/window/SystemWindow.h"
struct AndroidWindowInfo : public WindowInfo {
	struct android_app* appState;
};

#endif