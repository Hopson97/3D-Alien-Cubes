#version 330 core

in float zPosition;
in float currentTime;

in vec2 texCoord;

uniform sampler2D txr;
/*
void colour()
{
    float c     = sin(currentTime);
    float c2    = zPosition / 30;

    if ( c2 < 0.3)
    {
        c2 = 0.3;
    }
    //gl_FragColor = vec4 ( c * c2, c2, c2, 1.0f);
    //gl_FragColor = texture( txr, texCoord) * vec4 ( c * c2, c2, c2, 1.0f);
    vec3  colour = texture( txr, texCoord);
    //gl_FragColor = texture ( txr, texture ) * vec4 ( 1,1,1,1);

    if ( colour == vec3(1.0f, 1.0f, 1.0f ) )
    {
        discard;
    }

    gl_FragColor = vec4(colour, 1.0f );
}
*/
void main()
{
    //colour();

    vec3 colour = vec3(texture2D(txr, texCoord));

    if ( colour == vec3(1.0f, 1.0f, 1.0f ) )
    {
        discard;
    }

    gl_FragColor = vec4(colour, 1.0f );
}
