package com.example.videogles

class GLES3JNILIB {
    companion object {
        init {
            System.loadLibrary("videogles")
        }

        @JvmStatic
        external fun init()

        @JvmStatic
        external fun resize(width: Int, height: Int)

        @JvmStatic
        external fun step()
    }
}