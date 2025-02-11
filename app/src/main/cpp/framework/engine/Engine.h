//
// Created by MSD on 30/01/2025.
//

#ifndef VIDEOGLES_ENGINE_H
#define VIDEOGLES_ENGINE_H

#include <android/native_window.h>
#include "../core/Renderer/Renderer.h"

class Engine {
public:
    Engine();
    void SetWindow(ANativeWindow* native_window);
private:
    nativecpp::EGLRenderer egl_renderer_;
};

#endif //VIDEOGLES_ENGINE_H
