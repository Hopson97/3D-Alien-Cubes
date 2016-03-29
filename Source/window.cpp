#include "window.h"
#include <GL/glew.h>

Window :: Window()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;

    window.create(sf::VideoMode( win::WINDOW_WIDTH, win::WINDOW_HEIGHT),
                  "ayyyyy lmao",
                  sf::Style::Close,
                  settings);
    window.setFramerateLimit(120);                                                   //Set it's frame rate limit

    window.setPosition({-1500,0});

    window.setMouseCursorVisible( false );

    glewExperimental = GL_TRUE; //GLEW
    glewInit();

    glViewport(0, 0, win::WINDOW_WIDTH, win::WINDOW_HEIGHT);  //OpenGL, cull faces to improve performance
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void
Window :: update ()
{
    window.display();
    events();
}

void
Window :: events ()
{
    sf::Event e;

    while ( window.pollEvent ( e ) ) {
        if ( e.type == sf::Event::Closed ) window.close();

        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) ) window.close();
    }
}

void
Window :: clear ()
{
    float time = clock.getElapsedTime().asSeconds();

    //glClearColor( 1, 0, 0, 1 );
    glClearColor( sin(time + 5), 1, 1, 1 );
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
