//
// Created by Humayun Mustafa on 30/12/2024.
//

#ifndef VIDEOGLES_LOGGING_H
#define VIDEOGLES_LOGGING_H
#include "android/log.h"
#include "string.h"
#include <EGL/egl.h>


/// Cases for EGL logging. Currently only know errors are added.
/// Will update the function later accordingly.

const char* eglErrorString(EGLint error) {
    switch (error) {
        case EGL_NOT_INITIALIZED: return "EGL is not initialized! ";
        case EGL_BAD_ACCESS: return "Cannot access EGL (Bad Access)";
//        case EGL_NO_DISPLAY: return "Display not set for EGL"; TODO: Find out a viable replacement for this
        case EGL_BAD_CONFIG: return "EGL not configured correctly";
        case EGL_BAD_CONTEXT: return "EGL context is not set (Bad Context)";
        default: return "EGL error not specified in this app";

    }
}

#define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, __FILENAME__, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, __FILENAME__, __VA_ARGS__)

#define CHECK_RET_EGL(func) \
    do {                \
        if(!(func)) {   \
            EGLint error = eglGetError(); \
            LOGE("EGL function %s failed with error code: 0x%x (%s)", \
                #func, error, eglErrorString(error));                 \
        }               \
    } while(0);

#define CHECK_RET(func) \
    do {                \
        if(!(func)) {   \
            LOGE("Function %s does not returned OK state ", #func); \
        }               \
    } while(0);


#endif //VIDEOGLES_LOGGING_H
