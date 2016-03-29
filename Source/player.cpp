#include "player.h"

#include "window.h"

#include <iostream>
#include <cmath>
#include "fov_dance.h"

FOVdance d;

void
Player :: update      (  glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window, const float time, const float dt  )
{
    if ( getPosition().y < height )      changeVelocity ( { 0, -mFallSpeed * dt, 0 } );
    if ( getPosition().y >= height  )    setPosition    ( { getPosition().x, height, getPosition().z } );

    setVelocity( { getVelocity().x * 0.9, getVelocity().y, getVelocity().z * 0.9 } );

    input ( window, dt );

    //d.update( FOV );

    walkInput( dt );
    //checkVelocity();
    changePosition ( { -getVelocity().x, -getVelocity().y, -getVelocity().z } );

    view =  glm::translate      ( view,  getPosition() );
    proj =  glm::perspective    ( glm::radians( FOV ), win::WINDOW_WIDTH / win::WINDOW_HEIGHT, 0.01f, 100.0f );

    glm::mat4 yRotationMatrix;
    glm::mat4 xRotationMatrix;

    yRotationMatrix = glm::rotate( yRotationMatrix, glm::radians ( getRotation().y + 90 ),   glm::vec3 ( 0, 1, 0 ) );
    xRotationMatrix = glm::rotate( xRotationMatrix, glm::radians ( getRotation().x ),        glm::vec3 ( 1, 0, 0 ) );

    glm::mat4 finalRotation = xRotationMatrix * yRotationMatrix;

    proj = proj * finalRotation;
}

void
Player :: input       ( sf::RenderWindow& window, const float dt )
{
    mouseInput  ( window );
    jumpInput   ( dt );
    fovInput    ();
}

void
Player :: mouseInput  ( sf::RenderWindow& window )
{
    mMouseController.getRot( getRotationRef(), window );
}

void
Player :: walkInput   ( const float dt )
{
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::W ) )
    {
        changeVelocity( { 0, 0, ( mSpeedChange * sin (  glm::radians ( getRotation().y ) ) ) * dt         } );
        changeVelocity( {       ( mSpeedChange * cos (  glm::radians ( getRotation().y ) ) ) * dt, 0, 0   } );
    }
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::S ) )
    {
        changeVelocity( { 0, 0, ( -mSpeedChange * sin (  glm::radians ( getRotation().y ) ) ) * dt         } );
        changeVelocity( {       ( -mSpeedChange * cos (  glm::radians ( getRotation().y ) ) ) * dt, 0, 0   } );
    }
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::A ) )
    {
        changeVelocity( { 0, 0, ( -mSpeedChange * sin (  glm::radians ( getRotation().y + 90 ) ) ) * dt         } );
        changeVelocity( {       ( -mSpeedChange * cos (  glm::radians ( getRotation().y + 90 ) ) ) * dt, 0, 0   } );
    }
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::D ) )
    {
        changeVelocity( { 0, 0, ( mSpeedChange * sin (  glm::radians ( getRotation().y + 90  ) ) ) * dt         } );
        changeVelocity( {       ( mSpeedChange * cos (  glm::radians ( getRotation().y + 90  ) ) ) * dt, 0, 0   } );
    }
}

void
Player :: jumpInput   ( const float dt )
{
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && getPosition().y == height  )
    {
        changeVelocity ( { 0, mJumpSpeed * dt, 0 } );
    }
}

void
Player :: fovInput ()
{
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::P) )
    {
        FOV += FOV_CHANGE;
        if ( FOV > 179 ) FOV = 179;
    }
    else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::O) )
    {
        FOV -= FOV_CHANGE;
        if ( FOV < 1 ) FOV = 1;
    }
}

void
Player :: checkVelocity ()
{
    if ( getVelocity().x >= mMaxSpeed ) setVelocity( { mMaxSpeed, getVelocity().y, getVelocity().z } );

    if ( getVelocity().x >= mMaxSpeed ) setVelocity( { getVelocity().z, getVelocity().y, mMaxSpeed } );
}

