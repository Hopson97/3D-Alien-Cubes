#include "cube.h"
#include "rand.h"
#include "window.h"
#include "player.h"
#include "fps_counter.h"
#include "model.h"

#include <SFML/Audio.hpp>

#include <thread>

int
main()
{
    srand(time(NULL));


    int numCubes = 100 ;

    Window  window;
    Player  player ( -numCubes / 2, -numCubes / 2 );

    std::vector<Cube> cubes;

    //float startY = -2;
    //float endY = -5;

    for ( float z = numCubes; z > 0 ; z-- ) {
        for ( float x = 0; x < numCubes ; x++ ) {
            //for ( float y = startY ; y > endY; y-- ) {
                cubes.emplace_back( glm::vec3(x, 0 , z), false );
            //}
        }
    }

    int start = 3;

    for ( int i = 0; i < numCubes ; i++) {
        cubes.emplace_back( glm::vec3((float)random::num(0, numCubes ),
                                      start,
                                      ( float ) random::num( 0, numCubes)), true );

        cubes.emplace_back( glm::vec3((float)random::num(0, numCubes ),
                                      start + 1,
                                      ( float ) random::num( 0, numCubes)), true );

        cubes.emplace_back( glm::vec3((float)random::num(0, numCubes ),
                                      start + 2,
                                      ( float ) random::num( 0, numCubes)), true );
    }

    cubes.emplace_back( glm::vec3(numCubes/2, 20, numCubes/2 ), true );

    cubes.back().setScale( { 10, 10, 10 } );

    sf::Clock c;
    sf::Clock FPSclock;
    FPS_Counter fpsCounter;

    Model cubeModel;

    std::cout << "Vector size: " << cubes.size() << std::endl;

    float dt;
    while ( window.get().isOpen() ) {
        window.clear();

        dt = FPSclock.restart().asSeconds();

        glm::mat4 proj;
        glm::mat4 view;
        float time = c.getElapsedTime().asSeconds();

        player.update( view, proj, window.get(), time, dt );

        glm::mat4 pvMat = proj * view;

        //Cube models
        cubeModel.bind();
        for ( auto& cube : cubes) {
            cube.update ( pvMat, window.get(), time, cubeModel.getShaderID(), dt );
            glDrawElements ( GL_TRIANGLES, cubeModel.getIndexCount() , GL_UNSIGNED_INT, 0);
        }
        cubeModel.unBind();

        window.get().pushGLStates();
        window.get().resetGLStates();
        //Any SFML drawing goes here...
        window.get().popGLStates();

        window.update();

        fpsCounter.update();
    }
    return 0;
}
