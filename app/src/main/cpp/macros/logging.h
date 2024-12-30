//
// Created by Humayun Mustafa on 30/12/2024.
//

#ifndef VIDEOGLES_LOGGING_H
#define VIDEOGLES_LOGGING_H
#include "android/log.h"
#include "string.h"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, __FILENAME__, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, __FILENAME__, __VA_ARGS__)

#define CHECK_RET_EGL(func) \
    do {                \
        if(!(func)) {   \
            ELGint error = eglGetError(); \
            LOGE("EGL function %s failed with error code: 0x%x (%s)", \
                #func, error, elgErrorString(error));                 \
        }               \
    } while(0)

#define CHECK_RET(func) \
    do {                \
        if(!(func)) {   \
            LOGE("Function %s does not returned OK state ", #func); \
        }               \
    } while(0)

#endif

#endif //VIDEOGLES_LOGGING_H
