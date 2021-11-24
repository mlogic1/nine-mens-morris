#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;

out vec2 texCoord;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   texCoord = vec2(texCoords.x, texCoords.y);
   position = vec3(gl_Position);
}