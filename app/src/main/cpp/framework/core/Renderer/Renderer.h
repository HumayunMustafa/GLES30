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
        bool InitializeWindow(ANativeWindow* window);
        void DrawFrame();
        ~EGLRenderer() override {}
        void Initialize();
    private:
    };

} // namespace

#endif //VIDEOGLES_RENDERER_H
