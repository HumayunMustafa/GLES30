//
// Created by Humayun Mustafa on 30/12/2024.
//

#ifndef VIDEOGLES_LOGGING_H
#define VIDEOGLES_LOGGING_H
#include "android/log.h"
#include "string.h"
#include <stdexcept>
#include <EGL/egl.h>
#include <string>


/// Cases for EGL logging. Currently only known errors are added.
/// Will update the function later accordingly.

const char* EglErrorString(EGLint error) {
    switch (error) {
        case EGL_NOT_INITIALIZED: return "EGL is not initialized! ";
        case EGL_BAD_ACCESS: return "Cannot access EGL (Bad Access).";
//        case EGL_NO_DISPLAY: return "Display not set for EGL"; TODO: Find out a viable replacement for this
        case EGL_BAD_CONFIG: return "EGL not configured correctly.";
        case EGL_BAD_CONTEXT: return "EGL context is not set (Bad Context).";
        case EGL_BAD_PARAMETER: return "Parameter passed is not correct.";
        default: return "EGL error not specified in this app.";

    }
}

#define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, __FILENAME__, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, __FILENAME__, __VA_ARGS__)

#define CHECK_RET_EGL(func) \
    do {                    \
        EGLint egl_error = eglGetError();    \
        if(!(func)) {   \
            const char* error_str = EglErrorString(egl_error); \
            LOGE("EGL function %s failed with error code: 0x%x (%s)", \
                #func, egl_error, error_str);     \
            throw std::runtime_error(std::string("EGL function ") + #func + \
                                     " failed with error code: 0x" + \
                                     std::to_string(egl_error) + " (" + \
                                     error_str + ")"); \
        }               \
    } while(0);

#define CHECK_RET(func) \
    do {                \
        if(!(func)) {   \
            LOGE("Function %s does not returned OK state ", #func); \
            throw std::runtime_error(std::string("function name ") + #func + \
                 ")"); \
        }               \
    } while(0);

/// This function to print  the EGL configs. Might be necessary in some case in future
void LogEglConfigs(EGLDisplay display) {
    EGLint numConfigs;
    EGLConfig configs[4];

    CHECK_RET_EGL(eglGetConfigs(display, configs, 4, &numConfigs));
    LOGD("Number of configs: %d", numConfigs);
    for(int i = 0; i < numConfigs; i++) {
        EGLint redSize, greenSize, blueSize, alphaSize, depthSize, stencilSize;
        eglGetConfigAttrib(display, configs[i], EGL_RED_SIZE, &redSize);
        eglGetConfigAttrib(display, configs[i], EGL_GREEN_SIZE, &greenSize);
        eglGetConfigAttrib(display, configs[i], EGL_BLUE_SIZE, &blueSize);
        eglGetConfigAttrib(display, configs[i], EGL_ALPHA_SIZE, &alphaSize);
        eglGetConfigAttrib(display, configs[i], EGL_DEPTH_SIZE, &depthSize);
        eglGetConfigAttrib(display, configs[i], EGL_STENCIL_SIZE, &stencilSize);
        LOGD("Config %d: R:%d G:%d B:%d A:%d Depth:%d Stencil:%d",
             i, redSize, greenSize, blueSize, alphaSize, depthSize, stencilSize);
    }
}

#endif //VIDEOGLES_LOGGING_H
