#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_videogles_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videogles_GLES3JNILIB_init(JNIEnv *env, jclass clazz) {
    // TODO: implement init()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videogles_GLES3JNILIB_resize(JNIEnv *env, jclass clazz, jint width, jint height) {
    // TODO: implement resize()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_videogles_GLES3JNILIB_step(JNIEnv *env, jclass clazz) {
    // TODO: implement step()
}