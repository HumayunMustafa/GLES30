//
// Created by MSD on 30/01/2025.
//
#include "Engine.h"

Engine::Engine() {
    egl_renderer_.GetInstance().Initialize();
}

void Engine::SetWindow(ANativeWindow *native_window) {
    egl_renderer_.SetWindow(native_window);
}
