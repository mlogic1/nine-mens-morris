package mlogic1.morrisgame.rendering;

public class CppRenderer
{
    public CppRenderer()
    {

    }

    // native methods
    public native int AndroidMain(int width, int height);
    public native int AndroidUpdate();
    public native int AndroidOnTouchPressed(int x, int y);
    public native int AndroidUpdateCursor(int x, int y);
    public native int AndroidOnTouchReleased();
}
