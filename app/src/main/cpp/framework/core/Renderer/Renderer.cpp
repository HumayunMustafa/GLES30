//
// Created by MSD on 07/02/2025.
//

#include "Renderer.h"
#include "../../../macros/logging.h"

namespace nativecpp {

    void EGLRenderer::Initialize() {
        EGLRenderer();
    }

    EGLRenderer::EGLRenderer() {
        EGLint major_version;
        EGLint minor_version;
        EGLint num_configs;
        EGLint format;

        display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if(display_ == EGL_NO_DISPLAY) {
            throw std::runtime_error("No Native Windowing System Detected");
        }
        CHECK_RET_EGL(eglInitialize(display_, &major_version, &minor_version));
        LOGD("EGL version major: %d , minor: %d", major_version, minor_version);
        CHECK_RET_EGL(eglChooseConfig(display_, attrib_list_, &config_, 1, &num_configs));
        CHECK_RET_EGL(eglGetConfigAttrib(display_, config_, EGL_NATIVE_VISUAL_ID, &format));
    }

    void EGLRenderer::SetWindow(ANativeWindow* window) {
        window_ = window;
        surface_ = eglCreateWindowSurface(display_, config_, window_, attrib_list_);
        if(surface_ == EGL_NO_SURFACE) {
            switch (eglGetError()) {
                case EGL_BAD_MATCH:
                    LOGE("EGL_BAD_MATCH error");
                    break;
                case EGL_BAD_CONFIG:
                    LOGE("EGL_BAD_CONFIG error");
                    break;
                case EGL_BAD_NATIVE_WINDOW:
                    LOGE("EGL_BAD_NATIVE_WINDOW error");
                    break;
                case EGL_BAD_ALLOC:
                    LOGE("EGL_BAD_ALLOC error ");
                    break;
            }
        }
    }

} // namespace
