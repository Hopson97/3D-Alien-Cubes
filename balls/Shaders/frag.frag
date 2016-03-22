#version 330 core

out vec4 color;

in float z;
in float time;

void main()
{
    //color = vec4(1, z / 10, z / 10, 1.0f);

    float c = sin(time);

    color = vec4 ( c * z / 10, z / 10, z / 10, 1.0f);

}
