//
// Created by MSD on 07/02/2025.
//

#include "Renderer.h"
#include "../../../macros/logging.h"

namespace nativecpp {

    /// The below function is written using reference from book
    /// OpenGL ES 3.0: Programming Guide
    bool EGLRenderer::InitializeWindow(ANativeWindow *window) {
        EGLNativeWindowType n_window = window;
        const EGLint config_attrib[] = {
                EGL_RENDERABLE_TYPE, EGL_WINDOW_BIT,
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_DEPTH_SIZE, 24,
                EGL_NONE
        };
        const EGLint context_attrib[] = {
                EGL_CONTEXT_CLIENT_VERSION, 3,
                EGL_NONE
        };
        EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if(display == EGL_NO_DISPLAY) {
            return EGL_FALSE;
        }
        EGLint major, minor;
        CHECK_RET_EGL(eglInitialize(display, &major, &minor));
        EGLConfig config;
        EGLint  num_configs;
        CHECK_RET_EGL(eglChooseConfig(display,config_attrib,&config, 1, &num_configs));
        EGLSurface surface = eglCreateWindowSurface(display, config, n_window, NULL);
        if(surface == EGL_NO_SURFACE) {
            return EGL_FALSE;
        }
        EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attrib);
        if(context == EGL_NO_CONTEXT) {
            return EGL_FALSE;
        }
        CHECK_RET_EGL(eglMakeCurrent(display, window, window, context));
        return EGL_TRUE;
    }

} // namespace
