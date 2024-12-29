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
//import androidx.compose.ui.graphics.Color
import com.example.videogles.databinding.ActivityMainBinding
import java.io.InputStream

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private val surfaceView: SurfaceView
        get() = binding.sampleImageView

    val surfaeBitmap : Bitmap? =  null

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
                Log.d("SurfaceView", "Surface created - Valid: ${holder.surface.isValid}")
                Log.d("SurfaceView", "Surface size: ${surfaceView.width}x${surfaceView.height}")
                surfaceView.visibility = View.VISIBLE
                surfaeBitmap?.let { bitmap: Bitmap ->  drawBitmapOnSurface(bitmap)}
            }

            override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
                Log.d("SurfaceView", "Surface changed - Size: ${width}x${height}")
            }

            override fun surfaceDestroyed(holder: SurfaceHolder) {
                Log.d("SurfaceView", "Surface destroyed")
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
                    displayImageOnSurfaceView(selectedImageUri)
                }
            }
        }

    private fun displayImageOnSurfaceView(imageUri: Uri) {
//        val inputStream: InputStream? = contentResolver.openInputStream(imageUri)
//        val bitmap: Bitmap = BitmapFactory.decodeStream(inputStream)
//        val canvas = surfaceView.holder.lockCanvas()
//        if (canvas != null) {
//            canvas.drawBitmap(bitmap, 0f, 0f, null)
//            surfaceView.holder.unlockCanvasAndPost(canvas)
//        }
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
                    val scaleX = surfaceWidth / bitmap.width
                    val scaleY = surfaceHeight / bitmap.height
                    val scale = maxOf(scaleX, scaleY)  // Use max for "centerCrop" effect

                    // Calculate translation to center the image
                    val left = (surfaceWidth - (bitmap.width * scale)) / 2f
                    val top = (surfaceHeight - (bitmap.height * scale)) / 2f

                    val matrix = Matrix().apply {
                        postScale(scale, scale)
                        postTranslate(left, top)
                    }

                    it.drawBitmap(bitmap, matrix, null)
                    surfaceView.holder.unlockCanvasAndPost(it)
                }

                bitmap.recycle()
            }
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    private fun drawBitmapOnSurface(bitmap: Bitmap) {
        if (!surfaceView.holder.surface.isValid) {
            Log.e("SurfaceView", "Surface is not valid")
            return
        }

        try {
            val canvas = surfaceView.holder.lockCanvas()
            if (canvas == null) {
                Log.e("SurfaceView", "Canvas is null")
                return
            }

            try {
                // Clear the canvas
                canvas.drawColor(Color.BLACK)

                val surfaceWidth = surfaceView.width.toFloat()
                val surfaceHeight = surfaceView.height.toFloat()

                Log.d("SurfaceView", "Surface dimensions: $surfaceWidth x $surfaceHeight")
                Log.d("SurfaceView", "Bitmap dimensions: ${bitmap.width} x ${bitmap.height}")

                // Calculate scaling to fill the surface while maintaining aspect ratio
                val scaleX = surfaceWidth / bitmap.width
                val scaleY = surfaceHeight / bitmap.height
                val scale = maxOf(scaleX, scaleY)

                val scaledWidth = bitmap.width * scale
                val scaledHeight = bitmap.height * scale
                val left = (surfaceWidth - scaledWidth) / 2f
                val top = (surfaceHeight - scaledHeight) / 2f

                val matrix = Matrix().apply {
                    postScale(scale, scale)
                    postTranslate(left, top)
                }

                Log.d("SurfaceView", "Drawing with scale: $scale, left: $left, top: $top")
                canvas.drawBitmap(bitmap, matrix, null)
            } finally {
                surfaceView.holder.unlockCanvasAndPost(canvas)
                Log.d("SurfaceView", "Canvas unlocked and posted")
            }
        } catch (e: Exception) {
            Log.e("SurfaceView", "Error drawing bitmap", e)
        }
    }

    external fun stringFromJNI(): String
}
