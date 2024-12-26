package com.example.videogles


import android.content.Context
import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GLES3JNIView(context: Context) : GLSurfaceView(context) {
    init {
        // Pick an EGLConfig with RGB8 color, 16-bit depth, no stencil,
        // supporting OpenGL ES 2.0 or later backwards-compatible versions.
        setEGLConfigChooser(8, 8, 8, 0, 16, 0)
        setEGLContextClientVersion(3)
        setRenderer(Renderer())
    }

    private class Renderer : GLSurfaceView.Renderer {
        override fun onDrawFrame(gl: GL10?) {
            GLES3JNILIB.step()
        }

        override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
            GLES3JNILIB.resize(width, height)
        }

        override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
            GLES3JNILIB.init()
        }
    }
}