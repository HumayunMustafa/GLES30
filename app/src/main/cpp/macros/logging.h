//
// Created by Humayun Mustafa on 30/12/2024.
//

#ifndef VIDEOGLES_LOGGING_H
#define VIDEOGLES_LOGGING_H
#include "android/log.h"
#include "string.h"

#define DEBUG_MODE

#if DEBUG_MODE 1
#define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, __FILENAME__, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, __FILENAME__, __VA_ARGS__)
#endif

#endif //VIDEOGLES_LOGGING_H
