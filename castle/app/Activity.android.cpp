#include <stdlib.h>
#include <jni.h>

#include <android/log.h>
#define LOGI(...)((void)__android_log_print(ANDROID_LOG_INFO, "Citadel", __VA_ARGS__))

#include <string>
std::string gExternalStorage;
std::string gAPKName;

std::string ConvertJString(JNIEnv* env, jstring str) {
	if (!str) { return std::string(); }
	const jsize len = env->GetStringUTFLength(str);
	const char* strChars = env->GetStringUTFChars(str, (jboolean*)0);
	std::string result(strChars, len);
	env->ReleaseStringUTFChars(str, strChars);
	return result;
}

extern "C" {
	JNIEXPORT void JNICALL Java_com_bastiongames_citadel_CitadelActivity_OnCreateNative(JNIEnv* env, jobject obj, jstring externalStorageName) {

	}

	JNIEXPORT void JNICALL Java_com_bastiongames_citadel_CitadelActivity_SetSurface(JNIEnv* env, jclass clazz, jobject surface) {
	}

	JNIEXPORT void JNICALL Java_com_bastiongames_citadel_CitadelActivity_SetSurfaceSize(JNIEnv* env, jclass clazz, int width, int height) {
	}

	JNIEXPORT void JNICALL Java_com_bastiongames_citadel_CitadelActivity_DrawFrame(JNIEnv* env, jobject obj) {
	}

	JNIEXPORT void JNICALL Java_com_bastiongames_citadel_CitadelActivity_SetAPKName(JNIEnv* env, jobject obj, jstring apkName) {
	}

	JNIEXPORT void JNICALL Java_com_bastiongames_citadel_CitadelActivity_ExitNative(JNIEnv* env, jobject obj) {
	}

	JNIEXPORT void JNICALL Java_com_bastiongames_citadel_CitadelActivity_SendMotion(JNIEnv* env, jobject obj, int pointerId, int x, int y, bool pressed, int flag) {
	}
}