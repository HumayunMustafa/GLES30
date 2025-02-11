#include <jni.h>
#include <string>
#include "framework/engine/Engine.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>


static ANativeWindow *native_window_ptr = 0;
static std::unique_ptr<Engine> engine = nullptr;

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_videogles_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_videogles_JNIBridge_initScreenNative(JNIEnv *env, jclass clazz, jobject surface) {
    if(surface != 0) {
        native_window_ptr = ANativeWindow_fromSurface(env, surface);
        engine->SetWindow(native_window_ptr);
    }


}