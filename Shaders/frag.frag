#version 330 core

out vec4 color;

in float z;
in float time;

void main()
{
    //color = vec4(0, z / 10, 0, 1.0f);

    float c = sin(time);

    float c2 = z/10;

    if ( c2 < 0.1 ) c2 = 0.1;

    color = vec4 ( c * c2, c2, c2, 1.0f);



}
