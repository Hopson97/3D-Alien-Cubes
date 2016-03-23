#include "cube.h"
#include "rand.h"
#include "ballthing.h"
#include "mousecontroller.h"
#include "window.h"

void
windowEvents ( sf::Window& window );

void
lockMouse ( sf::Window& window );

int
main()
{
    srand(time(NULL));

    constexpr int FOV_CHANGE = 2;
    float FOV = 90.0f;

    int numCubes = 15;

    float forwardSpeed = 0;
    float maxSpeed = 0.21;

    float jumpSpeed = 0.35;
    float fallSpeed = 0.025;

    MouseController mouse;
    Window window;
/*
    std::vector<BallThing>  mBalls;
    for ( int i = 0; i < 2; i++) {
        mBalls.push_back( BallThing() );
    }
*/
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

    glm::vec3 vel { 0, 0, 0 };
    glm::vec3 pos { 0, 0, 0 };
    glm::vec3 rot { 0, 0, 0 };
    sf::Clock c;
    sf::Mouse::setPosition({0,0}, window.get() );
    while ( window.get().isOpen() ) {

        if ( pos.y < 0 ) vel.y += fallSpeed;
        if ( pos.y >= 0 ) pos.y = 0;

        std::cout << pos.y << std::endl;

        window.clear();


        if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::W ) ) {
            forwardSpeed = -maxSpeed;
        }
        else if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::S ) ) {
            forwardSpeed = maxSpeed;
        }
        else {
            forwardSpeed = 0;
        }

        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::P) ) {
            FOV += FOV_CHANGE;
            if ( FOV > 179 ) FOV = 179;
        }
        else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::O) ) {
            FOV -= FOV_CHANGE;
            if ( FOV < 1 ) FOV = 1;
        }
        if ( pos.y == 0 ) {
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space )) {
                vel.y -= jumpSpeed;
            }
        }

        pos.y += vel.y;



        mouse.getRot( rot, window.get() );

        float dz = forwardSpeed * sin (  glm::radians ( rot.y ) );
        float dx = forwardSpeed * cos (  glm::radians ( rot.y ) );

        pos.x += dx;
        pos.z += dz;

        glm::mat4 proj;
        glm::mat4 view;

        view =  glm::translate      (view,  pos);
        proj =  glm::perspective    (glm::radians(FOV), WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 100.0f);

        {
            glm::mat4 yRotMat;
            glm::mat4 xRotMat;

            yRotMat = glm::rotate( yRotMat, glm::radians ( rot.y + 90 ) ,   glm::vec3 ( 0, 1, 0 ) );
            xRotMat = glm::rotate( xRotMat, glm::radians ( rot.x ) ,        glm::vec3 ( 1, 0, 0 ) );

            glm::mat4 finalRot = xRotMat * yRotMat;

            proj = proj * finalRot;
        }

        float time = c.getElapsedTime().asSeconds();

        //GL drawing
        for ( auto& cube : cubes) {
            cube.update ( view, proj, time );
        }

        window.get().pushGLStates();
        window.get().resetGLStates();
        //Any SFML drawing goes here...
        window.get().popGLStates();

        window.update();
    }
    return 0;
}
