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
        static EGLRenderer& GetInstance() {
            static EGLRenderer instance;
            return instance;
        }
        bool InitializeEGL();
        void CreateWindow(ANativeWindow* window);
        void CreateContext();
        void MakeContextCurrent();
        void DrawFrame();
        ~EGLRenderer() override {}
    private:
        EGLNativeWindowType window_;
        EGLDisplay display_;
        EGLSurface surface_;
        EGLConfig config_;
        EGLContext context_;
    };

} // namespace

#endif //VIDEOGLES_RENDERER_H
