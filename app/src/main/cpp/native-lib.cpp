#include <jni.h>
#include <string>
#include "framework/engine/Engine.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>

/// The native app glue adds overhead and is ideal in cases when
/// building the native activity with no or little Kotlin/Java.
/// currently the jni approach is preferred.
//#include <android_native_app_glue.h>

static ANativeWindow *native_window_ptr = 0;
static std::unique_ptr<Engine> engine(new Engine());

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
    if(surface) {
        native_window_ptr = ANativeWindow_fromSurface(env, surface);
        engine->CreateWindow(native_window_ptr);
    }
}