package mlogic1.morrisgame.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;

import mlogic1.morrisgame.rendering.GLRenderer;

public class GLView extends GLSurfaceView
{
    private GLRenderer m_GLRenderer;

    public GLView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
        this.setEGLConfigChooser(8,8,8, 0, 16, 0);
        this.setEGLContextClientVersion(3);
        init();
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        // Log.d("ENGINE", event.toString());
        switch(event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                m_GLRenderer.OnTouchPressed((int)event.getX(), (int)event.getY());
                break;
            case MotionEvent.ACTION_MOVE:
                m_GLRenderer.OnTouchMove((int)event.getX(), (int)event.getY());
                break;
            case MotionEvent.ACTION_UP:
                m_GLRenderer.OnTouchReleased();
                break;
        }

        return true;
    }

    private void init()
    {
        m_GLRenderer = new GLRenderer(getContext());
        setRenderer(m_GLRenderer);
    }
}