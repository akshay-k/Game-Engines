#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 model; // loc of object in world coordinates
uniform mat4 view; // loc of camera
uniform mat4 projection; // perspective projection/clip to screen

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0f);
    Color = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}