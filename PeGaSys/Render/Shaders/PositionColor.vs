#version 330 core
layout (location = 4) in vec3 aPosition;
layout (location = 5) in vec3 aColor;


out vec3 ourColor;

uniform mat4 model; // loc of object in world coordinates
uniform mat4 view; // loc of camera
uniform mat4 projection; // perspective projection/clip to screen

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0f);
    ourColor = aColor;
}