#version 330 core

in float zPosition;
in float currentTime;

void main()
{
    float c = sin(currentTime);

    float c2 = zPosition / 13;

    if ( c2 < 0.3) c2 = 0.3;

    gl_FragColor = vec4 ( c * c2, c2, c2, 1.0f);
}
