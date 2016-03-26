#include "cube.h"
#include "rand.h"
#include "window.h"
#include "player.h"
#include "fps_counter.h"

#include <SFML/Audio.hpp>

#include <thread>



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
    FPS_Counter fpsCounter;

    while ( window.get().isOpen() ) {
        window.clear();

        glm::mat4 proj;
        glm::mat4 view;
        float time = c.getElapsedTime().asSeconds();

        player.update( view, proj, window.get(), time );

        //GL drawing
        for ( auto& cube : cubes) {
            cube.update ( view, proj, window.get(), time );
        }

        window.get().pushGLStates();
        window.get().resetGLStates();
        //Any SFML drawing goes here...
        window.get().popGLStates();

        window.update();

        fpsCounter.update();
    }
    return 0;
}
