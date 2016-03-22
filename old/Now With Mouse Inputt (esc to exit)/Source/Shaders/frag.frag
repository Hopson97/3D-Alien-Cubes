#version 330 core

out vec4 color;

in float z;

void main()
{
    color = vec4(1, z / 10, z / 10, 1.0f);
}
