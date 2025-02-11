//
// Created by MSD on 07/02/2025.
//

#include "Renderer.h"
#include "../../../macros/logging.h"

namespace nativecpp {

EGLRenderer::EGLRenderer() {
    EGLint major_version;
    EGLint minor_version;
    EGLConfig config;
    EGLint num_configs;
    EGLint format;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(display == EGL_NO_DISPLAY) {
        throw std::runtime_error("No Native Windowing System Detected");
    }
    CHECK_RET_EGL(eglInitialize(display, &major_version, &minor_version));
    LOGD("EGL version major: %d , minor: %d", major_version, minor_version);
    const EGLint config_attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_STENCIL_SIZE, 8,
            EGL_NONE
    };
    CHECK_RET_EGL(eglChooseConfig(display, config_attribs, &config, 1, &num_configs));
    CHECK_RET_EGL(eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format));


}

} // namespace
