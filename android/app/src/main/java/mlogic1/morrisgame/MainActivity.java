package mlogic1.morrisgame;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

import mlogic1.morrisgame.view.GLView;

public class MainActivity extends Activity
{
    static {
        // System.loadLibrary("morrisgame");
        System.loadLibrary("game");
    }

    private GLView m_mainActivityGLView;
    private AssetManager m_assetManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        SetFullscreenFlags();
        setContentView(R.layout.activity_main);
        m_mainActivityGLView = findViewById(R.id.MainGlView);

        // Asset manager
        m_assetManager = getAssets();
        SetAssetManager(m_assetManager);
    }

    // sets the application to fullscreen
    private void SetFullscreenFlags()
    {
        // fullscreen
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        // remove softkeys
        getWindow().getDecorView().setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
    }

    /*@Override
    protected void onResume()
    {
        super.onResume();
    }

    @Override
    protected void onPause()
    {
        super.onPause();
    }*/

    public native void SetAssetManager(AssetManager manager);
}