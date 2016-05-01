#include "game.h"

Game::Game()
{
    addCubes();

    std::cout << m_cubes.size() << std::endl;
}

void
Game :: run ()
{
    sf::Clock c;
    sf::Clock FPSclock;
    FPS_Counter fpsCounter;

    while ( m_window.get().isOpen() )
    {
        m_window.clear();

        float       dt;
        float       time;
        getTimes( dt, time, c, FPSclock );

        input   ( dt );
        update  ( dt, time );
        glDraw  ( dt, time );

        m_window    .update();
        fpsCounter  .update();
    }
}

void
Game :: input       ( const float dt )
{
    m_player.input ( m_window.get(), dt );
}

void
Game :: update ( const float dt, const float time  )
{
    m_player.update( time, dt );

    const float  biscrease = 0.07;
    //const float  biscrease = sin ( time ) * ( (float)m_numCubes / 200.0f );
    m_cubes.back().changeScale( { biscrease, biscrease, biscrease } );
    calcMatrices( );
}

void
Game :: calcMatrices    ( )
{
    mats = std::make_unique<Matrices>();

    mats->view =  glm::translate      ( mats->view,  -m_player.getPosition() );
    mats->proj =  glm::perspective    ( glm::radians( m_player.getFOV() ), win::WINDOW_WIDTH / win::WINDOW_HEIGHT, 0.01f, 10000.0f );

    glm::mat4 yRotationMatrix;
    glm::mat4 xRotationMatrix;
    glm::mat4 zRotationMatrix;

    xRotationMatrix = glm::rotate( xRotationMatrix, glm::radians ( m_player.getRotation().x ),        glm::vec3 ( 1, 0, 0 ) );
    yRotationMatrix = glm::rotate( yRotationMatrix, glm::radians ( m_player.getRotation().y + 90 ),   glm::vec3 ( 0, 1, 0 ) );
    zRotationMatrix = glm::rotate( zRotationMatrix, glm::radians ( m_player.getRotation().z ),        glm::vec3 ( 0, 0, 1 ) );
    glm::mat4 finalRotation = xRotationMatrix * yRotationMatrix * zRotationMatrix;

    mats->proj = mats->proj * finalRotation;
}


void
Game :: glDraw        ( const float dt, const float time )
{
    glm::mat4 pvMat = mats->proj * mats->view;

    cubeModel.bind();
    for ( auto& cube : m_cubes)
    {
        cube.update ( pvMat, m_window.get(), time, cubeModel.getShaderID(), dt );
        glDrawElements ( GL_TRIANGLES, cubeModel.getIndexCount(), GL_UNSIGNED_INT, 0);
    }
    cubeModel.unBind();
}

void
Game :: sfDraw ( const float dt )
{
    m_window.get().pushGLStates();
    m_window.get().resetGLStates();

    m_window.get().popGLStates();
}

void
Game :: getTimes    ( float& dt, float& time, sf::Clock& c, sf::Clock& FPSclock )
{
    dt = FPSclock.restart().asSeconds();

    time = c.getElapsedTime().asSeconds();
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
