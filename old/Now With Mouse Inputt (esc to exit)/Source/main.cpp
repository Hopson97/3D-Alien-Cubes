#include "cube.h"
#include "rand.h"
#include "ballthing.h"

void
windowEvents ( sf::Window& window);

float mouseXBefore;
float mouseYBefore;

void
yRot ( float& rotY )
{
    float rot = sf::Mouse::getPosition().x - mouseXBefore;

    rotY += rot;

    if ( rotY <= -360 ) rotY = 0;
    if ( rotY >= 360  ) rotY = 0;

    mouseXBefore = sf::Mouse::getPosition().x;
}

void
xRot ( float& rotX )
{
    float rot = sf::Mouse::getPosition().y - mouseYBefore;

    rotX += rot;

    if ( rotX <= -360 ) rotX = 0;
    if ( rotX >= 360  ) rotX = 0;

    mouseYBefore = sf::Mouse::getPosition().y;
}

void
calcuateRotations ( glm::vec3& rotVec )
{
    yRot( rotVec.y );
    xRot( rotVec.x );
}

int
main()
{
    srand(time(NULL));

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "Balls.",
                            sf::Style::None,
                            settings);
    window.setFramerateLimit(60);                                                   //Set it's frame rate limit

    window.setMouseCursorVisible( false );

    glewExperimental = GL_TRUE; //GLEW
    glewInit();

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  //OpenGL
    glEnable(GL_DEPTH_TEST);

    std::vector<Cube> cubes;

    int n = 10;

    for ( float z = n; z > -n ; z-- ) {
        for ( float x = -n; x < n ; x++ ) {
            cubes.emplace_back( glm::vec3(x, -2, z) );
        }
    }
    for ( int i = 0; i < 10; i++) {
        cubes.emplace_back( glm::vec3((float)random::num(-n, n), -1, (float)random::num(-n, n)) );
    }

    std::vector<BallThing>  mBalls;
    for ( int i = 0; i < 2; i++) {
        mBalls.push_back( BallThing() );
    }

    glm::vec3 pos { 0, 0, 0 };
    glm::vec3 rot { 0, 0, 0 };

    float currSpeed = 0;
    float maxSpeed = 0.1;

    while ( window.isOpen() ) {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) {
            currSpeed = -maxSpeed;
        }
        else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) {
            currSpeed = maxSpeed;
        }
        else {
            currSpeed = 0;
        }

        calcuateRotations( rot );

        float dz = currSpeed * sin (  (  (double) rot.y * ( 3.14159 / 180) ) );
        float dx = currSpeed * cos (  (  (double) rot.y * ( 3.14159 / 180) ) );

        pos.x += dx;
        pos.z += dz;

        glm::mat4 proj;
        glm::mat4 view;

        view =  glm::translate      (view,  pos);
        proj =  glm::perspective    (45.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

        glm::mat4 yRotMat;
        glm::mat4 xRotMat;

        yRotMat = glm::rotate( yRotMat, glm::radians ( rot.y + 90 ) ,   glm::vec3 ( 0, 1, 0 ) );
        xRotMat = glm::rotate( xRotMat, glm::radians ( rot.x ) ,        glm::vec3 ( 1, 0, 0 ) );

        proj = proj * xRotMat * yRotMat;


        window.clear({(unsigned char)random::num(20, 40), (unsigned char)random::num(0, 20), (unsigned char)random::num(154, 174), (unsigned char)1.0f});
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        //drawing
        {
            for ( auto& cube : cubes) {
                cube.update ( view, proj );
            }
        }
        window.pushGLStates();
        window.resetGLStates();

        for ( auto& ball : mBalls ) {
            ball.update ( window );
        }

        window.popGLStates();


        window.display();
        windowEvents(window);
    }

    return 0;
}

void
windowEvents ( sf::Window& window)
{
    sf::Event e;

    while ( window.pollEvent ( e ) ) {
        if ( e.type == sf::Event::Closed ) window.close();

        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) ) window.close();
    }
}
