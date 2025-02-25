//
// Created by MSD on 07/02/2025.
//

#include "Renderer.h"
#include "../../../macros/logging.h"

namespace nativecpp {

    /// The below function is written using reference from book
    /// OpenGL ES 3.0: Programming Guide
    bool EGLRenderer::InitializeEGL() {
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
        display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if(display_ == EGL_NO_DISPLAY) {
            return EGL_FALSE;
        }
        EGLint major, minor;
        CHECK_RET_EGL(eglInitialize(display_, &major, &minor));
        EGLint  num_configs;
        CHECK_RET_EGL(eglChooseConfig(display_,config_attrib,&config_, 1, &num_configs));
        return EGL_TRUE;
    }

    void EGLRenderer::DrawFrame() {
    }

    void EGLRenderer::CreateWindow(ANativeWindow *window) {
        window_ = window;
        surface_ = eglCreateWindowSurface(display_, config_, window_, NULL);
        CHECK_RET_EGL(surface_);
    }

    void EGLRenderer::CreateContext() {
        const EGLint attribList[] =
                {
                        // EGL_KHR_create_context is required
                        EGL_CONTEXT_CLIENT_VERSION, 3,
                        EGL_NONE
                };
        context_ = eglCreateContext(display_, config_, EGL_NO_CONTEXT, attribList);
        CHECK_RET_EGL(context_);
    }

    void EGLRenderer::MakeContextCurrent() {
        CHECK_RET_EGL(eglMakeCurrent(display_,surface_,surface_,context_));
    }

} // namespace
