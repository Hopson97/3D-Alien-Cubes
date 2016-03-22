#include "cube.h"
#include "rand.h"
#include "ballthing.h"
#include "mousecontroller.h"

void
windowEvents ( sf::Window& window);

int
main()
{

    float FOV = 90.0f;

    int numCubes = 15;

    float forwardSpeed = 0;
    float maxSpeed = 0.1;

    MouseController mouse;

    srand(time(NULL));
    sf::ContextSettings settings;
    settings.depthBits = 24;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "Balls.",
                            sf::Style::Resize,
                            settings);
    window.setFramerateLimit(120);                                                   //Set it's frame rate limit

    window.setPosition({0,0});

    glewExperimental = GL_TRUE; //GLEW
    glewInit();

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  //OpenGL, cull faces to improve performance
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    std::vector<BallThing>  mBalls;
    for ( int i = 0; i < 2; i++) {
        mBalls.push_back( BallThing() );
    }

    std::vector<Cube> cubes;

    for ( float z = numCubes; z > -numCubes ; z-- ) {
        for ( float x = -numCubes; x < numCubes ; x++ ) {
            cubes.emplace_back( glm::vec3(x, -2, z) );
        }
    }
    for ( int i = 0; i < numCubes ; i++) {
        cubes.emplace_back( glm::vec3((float)random::num(- numCubes, numCubes ),
                                      -1,
                                      ( float ) random::num( -numCubes, numCubes)) );

        cubes.emplace_back( glm::vec3((float)random::num(- numCubes, numCubes ),
                                      1,
                                      ( float ) random::num( -numCubes, numCubes)) );

        cubes.emplace_back( glm::vec3((float)random::num(- numCubes, numCubes ),
                                      3,
                                      ( float ) random::num( -numCubes, numCubes)) );
    }

    std::cout << cubes.size() << std::endl;

    glm::vec3 pos { 0, 0, 0 };
    glm::vec3 rot { 0, 0, 0 };
    sf::Clock c;
    sf::Mouse::setPosition({0,0}, window);
    while ( window.isOpen() ) {


        if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::W ) ) {
            forwardSpeed = -maxSpeed;
        }
        else if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::S ) ) {
            forwardSpeed = maxSpeed;
        }
        else {
            forwardSpeed = 0;
        }
/*
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) {
            sideSpeed = -maxSpeed;
        }
        else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) {
            sideSpeed = maxSpeed;
        }
        else
        {
            sideSpeed = 0;
        }
*/

        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::P) ) {
            FOV += 1.0f;
            if ( FOV > 178 ) FOV = 178;
        }
        else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::O) ) {
            FOV -= 1.0f;
            if ( FOV < 1 ) FOV = 1;
        }

        mouse.getRot( rot );

        float dz = forwardSpeed * sin (  glm::radians ( rot.y ) );
        float dx = forwardSpeed * cos (  glm::radians ( rot.y ) );

        pos.x += dx;
        pos.z += dz;

        glm::mat4 proj;
        glm::mat4 view;

        view =  glm::translate      (view,  pos);
        proj =  glm::perspective    (glm::radians(FOV), WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 100.0f);


        glm::mat4 yRotMat;
        glm::mat4 xRotMat;

        yRotMat = glm::rotate( yRotMat, glm::radians ( rot.y + 90 ) ,   glm::vec3 ( 0, 1, 0 ) );
        xRotMat = glm::rotate( xRotMat, glm::radians ( rot.x ) ,        glm::vec3 ( 1, 0, 0 ) );

        proj = proj * xRotMat * yRotMat;

        float time = c.getElapsedTime().asSeconds();
        glClearColor( 1, 0, 0, 1 );
        //glClearColor( sin(time), 1, 1, 1 );
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        //drawing
        {
            for ( auto& cube : cubes) {
                cube.update ( view, proj, time );
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
