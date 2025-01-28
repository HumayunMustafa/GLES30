package com.example.videogles

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Intent
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Color
import android.graphics.Matrix
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.provider.MediaStore
import android.util.Log
import android.view.SurfaceHolder
import android.view.SurfaceView
import android.view.View
import androidx.activity.result.contract.ActivityResultContracts
import com.example.videogles.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private val surfaceView: SurfaceView
        get() = binding.sampleImageView

    private var isSurfaceReady = false
    private var pendingImageUri: Uri? = null  // Store the pending image URI
    private var currentBitmap: Bitmap? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.galleryButton.setOnClickListener {
            openGalleryPicker()
        }

        // Initialize SurfaceView
        surfaceView.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceCreated(holder: SurfaceHolder) {
//                JNIBridge.initScreenNative(holder.surface)
                isSurfaceReady = true
                Log.d("SurfaceHolder", "surfaceCreated")
                // If there's a pending image URI, display it now
                pendingImageUri?.let {
                    displayImageOnSurfaceView(it)
                    pendingImageUri = null
                }
            }

            override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
                Log.d("SurfaceHolder", "surfaceChanged")
//                pendingImageUri?.let {
//                    displayImageOnSurfaceView(it)
//                    pendingImageUri = null
//                }
            }

            override fun surfaceDestroyed(holder: SurfaceHolder) {
                isSurfaceReady = false
            }
        })
    }

    @SuppressLint("IntentReset")
    private fun openGalleryPicker() {
        val galleryIntent = Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI)
        galleryIntent.type = "image/*"
        startForResult.launch(galleryIntent)
    }

    // Registering for Activity Result to handle the selected image
    private val startForResult =
        registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
            if (result.resultCode == Activity.RESULT_OK) {
                val selectedImageUri: Uri? = result.data?.data
                if (selectedImageUri != null) {
                    // Call displayImageOnSurfaceView with the selected image URI
                    displayImageOnSurfaceView(selectedImageUri)
                }
            }
        }

    private fun displayImageOnSurfaceView(imageUri: Uri) {
        if (!isSurfaceReady) {
            Log.e("SurfaceView", "Surface is not ready, storing the image URI for later.")
            pendingImageUri = imageUri  // Store the URI for later
            return
        }

        try {
            contentResolver.openInputStream(imageUri)?.use { inputStream ->
                val bitmap: Bitmap = BitmapFactory.decodeStream(inputStream)
                Log.d("SurfaceView", "displayImageOnSurfaceView:  ${bitmap.height}x${bitmap.width}")

                val canvas = surfaceView.holder.lockCanvas()
                canvas?.let {
                    // Clear canvas
                    it.drawColor(Color.BLACK)

                    // Get surface dimensions
                    val surfaceWidth = surfaceView.width.toFloat()
                    val surfaceHeight = surfaceView.height.toFloat()

                    // Calculate scaling factors
                    val scaleX = surfaceWidth / bitmap.width.toFloat()
                    val scaleY = surfaceHeight / bitmap.height.toFloat()
                    val scale = minOf(scaleX, scaleY)  // Use min for "fitCenter" effect

                    // Calculate new dimensions of the bitmap
                    val scaledWidth = bitmap.width * scale
                    val scaledHeight = bitmap.height * scale

                    // Calculate translation to center the image
                    val left = (surfaceWidth - scaledWidth) / 2f
                    val top = (surfaceHeight - scaledHeight) / 2f

                    val matrix = Matrix().apply {
                        postScale(scale, scale)
                        postTranslate(left, top)
                    }

                    it.drawBitmap(bitmap, matrix, null)
                    surfaceView.holder.unlockCanvasAndPost(it)
                }

                // Recycle the bitmap after drawing
                bitmap.recycle()
            }
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    external fun stringFromJNI(): String
}
