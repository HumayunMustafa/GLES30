//
// Created by MSD on 07/02/2025.
//

#include "Renderer.h"
#include "../../../macros/logging.h"

namespace nativecpp {

EGLRenderer::EGLRenderer() {
    EGLint major_version;
    EGLint minor_version;
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(display == EGL_NO_DISPLAY) {
        throw std::runtime_error("No Native Windowing System Detected");
    }
    CHECK_RET_EGL(eglInitialize(display, &major_version, &minor_version));
}

} // namespace
