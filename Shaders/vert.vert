#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform float time;

varying float zPosition;
varying float currentTime;

void set_outs ()
{
    zPosition = gl_Position.z;
    currentTime = time;
}

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);

    //gl_Position.y = (pow ((gl_Position.x + gl_Position.y), 2) / 15) - 1;

    set_outs ();
}
