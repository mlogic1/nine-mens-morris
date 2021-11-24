#version 300 es
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;
    
	out vec3 outPosition;
    out vec2 texCoord;
	
    void main()
    {
       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
       outPosition = vec3(gl_Position);
       texCoord = aTexCoord;
    }