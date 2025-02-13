//
// Created by MSD on 30/01/2025.
//
#include "Engine.h"

Engine::Engine() {

}

void Engine::InitializeWindow(ANativeWindow *native_window) {
    bool status = egl_renderer_.InitializeWindow(native_window);
    if(status == false) {
        throw std::runtime_error("window not initialized...");
    }
}
