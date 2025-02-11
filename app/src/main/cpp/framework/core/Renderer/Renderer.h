//
// Created by MSD on 07/02/2025.
//

#ifndef VIDEOGLES_RENDERER_H
#define VIDEOGLES_RENDERER_H

#include "EGL/egl.h"
#include "EGL/eglext.h"
#include <GLES3/gl3.h>
#include <android/native_window.h>

namespace nativecpp {
    /// This class will handle the rendering of everything in this app
    class Renderer {
    public:
        virtual ~Renderer() = 0;
    private:
    }; // class

    class EGLRenderer : Renderer {
    public:
        EGLRenderer();
        ~EGLRenderer() override {}

    private:
        EGLNativeWindowType window_ = nullptr;
    };

} // namespace

#endif //VIDEOGLES_RENDERER_H
