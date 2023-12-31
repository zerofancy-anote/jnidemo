package top.ntutn.testjni

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import androidx.annotation.Keep
import top.ntutn.testjni.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = string2FromJNI()
    }

    /**
     * A native method that is implemented by the 'testjni' native library,
     * which is packaged with this application.
     */
    @Keep
    external fun stringFromJNI(): String

    @Keep
    external fun string2FromJNI(): String

    companion object {
        // Used to load the 'testjni' library on application startup.
        init {
            System.loadLibrary("testjni")
        }
    }
}