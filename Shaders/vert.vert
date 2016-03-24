#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform float t;

out float z;
out float time;

void set_outs ()
{
    z = gl_Position.z;
    time = t;
}

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);

    //gl_Position.y = (pow ((gl_Position.x + gl_Position.y), 2) / 15) - 1;

    set_outs ();
}
