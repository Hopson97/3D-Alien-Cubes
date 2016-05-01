#include "player.h"

#include "window.h"

#include <iostream>
#include <cmath>

void
Player :: update      ( const float time, const float dt  )
{
    setVelocity( { getVelocity().x * 0.9, getVelocity().y, getVelocity().z * 0.9 } );

    changePosition ( { getVelocity().x * dt, getVelocity().y * dt, getVelocity().z * dt } );

    checkIfOnGround( dt );

    walkInput( dt );
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
        changeVelocity( { 0, 0, ( mSpeedChange * sin (  glm::radians ( getRotation().y ) ) )         } );
        changeVelocity( {       ( mSpeedChange * cos (  glm::radians ( getRotation().y ) ) ), 0, 0   } );
    }
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::S ) )
    {
        changeVelocity( { 0, 0, ( -mSpeedChange * sin (  glm::radians ( getRotation().y ) ) )         } );
        changeVelocity( {       ( -mSpeedChange * cos (  glm::radians ( getRotation().y ) ) ), 0, 0   } );
    }
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::A ) )
    {
        changeVelocity( { 0, 0, ( -mSpeedChange * sin (  glm::radians ( getRotation().y + 90 ) ) )         } );
        changeVelocity( {       ( -mSpeedChange * cos (  glm::radians ( getRotation().y + 90 ) ) ), 0, 0   } );
    }
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::D ) )
    {
        changeVelocity( { 0, 0, ( mSpeedChange * sin (  glm::radians ( getRotation().y + 90  ) ) )         } );
        changeVelocity( {       ( mSpeedChange * cos (  glm::radians ( getRotation().y + 90  ) ) ), 0, 0   } );
    }
}

void
Player :: jumpInput   ( const float dt )
{
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && onGround()  )
    {
        std::cout << "jump " << std::endl;
        jump( dt );
    }
}

void
Player :: jump  ( const float dt )
{
    changeVelocity ( { 0, mJumpSpeed, 0 } );
    isJumping = true;
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

const bool
Player :: onGround ()
{
    if ( getPosition().y <= groundHeight )
    {
        isJumping = false;
        setPosition( { getPosition().x, (int)groundHeight, getPosition().z } );
        setVelocity ( {getVelocity().x, 0, getVelocity().z} );
        return true;
    }
    return false;
}

void
Player :: checkIfOnGround ( const float dt )
{

    if ( !onGround() )
    {
        changeVelocity ( { 0, -mFallSpeed, 0 } );
    }
}
