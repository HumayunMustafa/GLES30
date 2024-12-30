package com.example.videogles

import android.view.Surface

class JNIBridge {
    companion object {
       init {
           System.loadLibrary("videogles")
       }

        @JvmStatic
        external fun initScreenNative(surface: Surface)
    }
}