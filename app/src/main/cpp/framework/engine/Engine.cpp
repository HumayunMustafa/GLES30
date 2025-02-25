//
// Created by MSD on 30/01/2025.
//
#include "Engine.h"

Engine::Engine() {

}

void Engine::InitializeWindow(ANativeWindow *native_window) {
    CHECK_RET(egl_renderer_.InitializeWindow(native_window));
}

void Engine::DrawFrame() {

}
