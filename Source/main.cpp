#include "cube.h"
#include "rand.h"
#include "ballthing.h"
#include "window.h"
#include "player.h"

void
windowEvents ( sf::Window& window );

void
lockMouse ( sf::Window& window );

int
main()
{
    srand(time(NULL));

    int numCubes = 15;

    Window  window;
    Player  player;

    std::vector<Cube> cubes;

    for ( float z = numCubes; z > -numCubes ; z-- ) {
        for ( float x = -numCubes; x < numCubes ; x++ ) {
            cubes.emplace_back( glm::vec3(x, -2, z), false );
        }
    }
    for ( int i = 0; i < numCubes ; i++) {
        cubes.emplace_back( glm::vec3((float)random::num(- numCubes, numCubes ),
                                      1,
                                      ( float ) random::num( -numCubes, numCubes)), true );

        cubes.emplace_back( glm::vec3((float)random::num(- numCubes, numCubes ),
                                      2,
                                      ( float ) random::num( -numCubes, numCubes)), true );

        cubes.emplace_back( glm::vec3((float)random::num(- numCubes, numCubes ),
                                      3,
                                      ( float ) random::num( -numCubes, numCubes)), true );
    }

    sf::Clock c;
    while ( window.get().isOpen() ) {

        window.clear();

        glm::mat4 proj;
        glm::mat4 view;

        player.update( view, proj, window.get() );


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
