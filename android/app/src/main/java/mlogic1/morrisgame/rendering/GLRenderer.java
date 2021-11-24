package mlogic1.morrisgame.rendering;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRenderer implements GLSurfaceView.Renderer
{
    final private CppRenderer m_cppRenderer;

    public GLRenderer()
    {
        m_cppRenderer = new CppRenderer();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        m_cppRenderer.AndroidMain();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        // todo
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        m_cppRenderer.AndroidUpdate();
    }
}
