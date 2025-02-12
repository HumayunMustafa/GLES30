//
// Created by MSD on 07/02/2025.
//

#ifndef VIDEOGLES_RENDERER_H
#define VIDEOGLES_RENDERER_H

#include "EGL/egl.h"
#include "EGL/eglext.h"
#include <GLES3/gl3.h>
#include <android/native_window.h>

const EGLint attrib_list_[] =  {
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

namespace nativecpp {
    /// This class will handle the rendering of everything in this app
    class Renderer {
    public:
        virtual ~Renderer() = 0;
    private:
    }; // class

    class EGLRenderer : Renderer {
    public:
        static EGLRenderer& GetInstance() {
            static EGLRenderer instance;
            return instance;
        }
        void SetWindow(ANativeWindow* window);
        EGLRenderer();
        ~EGLRenderer() override {}
        void Initialize();
    private:
        EGLNativeWindowType window_ = nullptr;
        EGLDisplay display_;
        EGLConfig config_;
        EGLSurface surface_;
    };

} // namespace

#endif //VIDEOGLES_RENDERER_H
