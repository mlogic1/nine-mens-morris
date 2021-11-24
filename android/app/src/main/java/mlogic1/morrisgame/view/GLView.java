package mlogic1.morrisgame.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

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

    private void init()
    {
        m_GLRenderer = new GLRenderer();
        setRenderer(m_GLRenderer);
    }
}