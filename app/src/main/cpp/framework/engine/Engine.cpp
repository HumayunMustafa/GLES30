//
// Created by MSD on 30/01/2025.
//
#include "Engine.h"

Engine::Engine() {
    egl_renderer_.InitializeEGL();
}

void Engine::CreateWindow(ANativeWindow *native_window) {
    egl_renderer_.CreateWindow(native_window);
}

void Engine::DrawFrame() {

}
