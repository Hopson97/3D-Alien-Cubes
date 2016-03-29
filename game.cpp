#include "game.h"

Game::Game()
{
    addCubes();
}

void
Game :: run ()
{
    sf::Clock c;
    sf::Clock FPSclock;
    FPS_Counter fpsCounter;

    glm::mat4 proj;
    glm::mat4 view;

    float dt;
    while ( m_window.get().isOpen() )
    {
        glm::mat4 proj;
        glm::mat4 view;

        m_window.clear();

        dt = FPSclock.restart().asSeconds();

        float time = c.getElapsedTime().asSeconds();

        m_player.update( view, proj, m_window.get(), time, dt );

        glm::mat4 pvMat = proj * view;

        //Cube models
        cubeModel.bind();
        for ( auto& cube : m_cubes)
        {
            cube.update ( pvMat, m_window.get(), time, cubeModel.getShaderID(), dt );
            glDrawElements ( GL_TRIANGLES, cubeModel.getIndexCount(), GL_UNSIGNED_INT, 0);
        }
        cubeModel.unBind();

        m_window.get().pushGLStates();
        m_window.get().resetGLStates();
        //Any SFML drawing goes here...
        m_window.get().popGLStates();

        m_window.update();

        fpsCounter.update();

        float  biscrease = abs ( sin ( time ) * 0.5 );
        m_cubes.back().changeScale( { biscrease, biscrease, biscrease } );
    }
}





void
Game :: addCubes()
{
    //Main floor cubes
    for ( float z = m_numCubes; z > 0 ; z-- )
    {
        for ( float x = 0; x < m_numCubes ; x++ )
        {
            m_cubes.emplace_back( glm::vec3(x, 0, z), false );
        }
    }

    //Floating cubes
    constexpr static int baseYPos = 3;
    for ( int i = 0; i < m_numCubes; i++)
    {
        //Layer 1
        m_cubes.emplace_back( glm::vec3 (   ( float ) random::num( 0, m_numCubes ),
                                            baseYPos,
                                            ( float ) random::num( 0, m_numCubes)), true );
        //Layer 2
        m_cubes.emplace_back( glm::vec3 (   ( float ) random::num( 0, m_numCubes ),
                                            baseYPos + 1,
                                            ( float ) random::num( 0, m_numCubes)), true );
        //Layer 3
        m_cubes.emplace_back( glm::vec3 (   ( float ) random::num( 0, m_numCubes ),
                                            baseYPos + 2,
                                            ( float ) random::num( 0, m_numCubes)), true );
    }

    //Big cube
    m_cubes.emplace_back( glm::vec3 ( m_numCubes / 2, 20, m_numCubes/2 ), true );
    m_cubes.back().setScale( { 0, 0, 0 } );
}
