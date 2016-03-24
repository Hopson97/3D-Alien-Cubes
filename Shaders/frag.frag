#version 330 core

out vec4 color;

in float z;
in float time;

void main()
{
    float c = sin(time);

    float c2 = z/13;

    if ( c2 < 0.3) c2 = 0.3;

    color = vec4 ( c * c2, c2, c2, 1.0f);



}
