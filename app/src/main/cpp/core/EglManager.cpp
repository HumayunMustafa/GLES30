//
// Created by Humayun Mustafa on 30/12/2024.
//

#include "EglManager.h"
#include "../macros/logging.h"

EGLManager::EGLManager() {
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(display == EGL_NO_DISPLAY) {
        LOGE("No Native Windowing System Found");
    }
    if(!eglInitialize(display, &majorVersion, &minorVersion)) {
        LOGE("EGL not initialized ");
    }
}

