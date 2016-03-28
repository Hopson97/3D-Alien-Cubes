#version 330 core

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec2 in_texCoords;

uniform mat4 pvMat;
uniform mat4 modelMatrix;
uniform float time;

out float zPosition;
out float currentTime;
out vec2 texCoord;

void set_outs ()
{
    zPosition = gl_Position.z;
    currentTime = time;

    texCoord = in_texCoords;
}

void main()
{
    gl_Position = pvMat * modelMatrix * vec4(position, 1.0);

    //gl_Position.y = (pow ((gl_Position.x + gl_Position.y), 2) / 15) - 1;

    set_outs ();


}




