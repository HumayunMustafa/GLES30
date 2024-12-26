package com.example.videogles

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Intent
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.provider.MediaStore
import android.widget.ImageView
import android.widget.TextView
import androidx.activity.result.contract.ActivityResultContracts
import com.example.videogles.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.galleryButton.setOnClickListener {
            openGalleryPicker()
        }
        // Example of a call to a native method
//        binding.sampleText.text = stringFromJNI()
    }

    @SuppressLint("IntentReset")
    private fun openGalleryPicker() {
        // Launch the gallery picker
        val galleryIntent = Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI)
        galleryIntent.type = "image/*"
        startForResult.launch(galleryIntent)
    }

    // Registering for Activity Result to handle the selected image
    private val startForResult =
        registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
            if (result.resultCode == Activity.RESULT_OK) {
                // Handle the image selected
                val selectedImageUri: Uri? = result.data?.data
                if (selectedImageUri != null) {
                    displayImage(selectedImageUri)
                }
            }
        }

    private fun displayImage(imageUri: Uri) {
        val imageView: ImageView = binding.sampleImageView
        imageView.setImageURI(imageUri)
    }

    /**
     * A native method that is implemented by the 'videogles' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

//    companion object {
//        // Used to load the 'videogles' library on application startup.
//        init {
//            System.loadLibrary("videogles")
//        }
//    }
}