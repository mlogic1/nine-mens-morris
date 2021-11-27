package mlogic1.morrisgame.rendering;

import android.content.Context;
import android.opengl.GLSurfaceView;

import java.nio.IntBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.opengles.GL11;

public class GLRenderer implements GLSurfaceView.Renderer
{
    final private CppRenderer m_cppRenderer;
    private Context m_context;

    public GLRenderer(Context context)
    {
        m_context = context;
        m_cppRenderer = new CppRenderer();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        IntBuffer b = IntBuffer.allocate(4);
        gl.glGetIntegerv(GL11.GL_VIEWPORT, b);
        m_cppRenderer.AndroidMain(b.get(2), b.get(3));
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        int x = 1;  // TODO check if this thing gets called
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        m_cppRenderer.AndroidUpdate();
    }

    public void OnTouchPressed(int x, int y)
    {
        m_cppRenderer.AndroidOnTouchPressed(x, y);
    }

    public void OnTouchMove(int x, int y)
    {
        m_cppRenderer.AndroidUpdateCursor(x, y);
    }

    public void OnTouchReleased()
    {
        m_cppRenderer.AndroidOnTouchReleased();
    }
}
