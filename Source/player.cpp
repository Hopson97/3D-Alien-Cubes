#include "player.h"

#include "window.h"

#include <iostream>
#include <cmath>

void
Player :: update      ( const float time, const float dt  )
{
    setVelocity( { getVelocity().x * 0.9, getVelocity().y, getVelocity().z * 0.9 } );
    checkIfOnGround( dt );

    walkInput( dt );
    changePosition ( { getVelocity().x, getVelocity().y, getVelocity().z } );
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
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && onGround()  )
    {
        jump( dt );
    }
}

void
Player :: jump  ( const float dt )
{
    changeVelocity ( { 0, 0.5, 0 } );
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

    if ( getPosition().y < groundHeight )
    {
        isJumping = false;
        setPosition( { getPosition().x, groundHeight, getPosition().z } );
        return true;
    }
    return false;
}

void
Player :: checkIfOnGround ( const float dt )
{

    if ( !onGround() )
    {
        changeVelocity ( { 0, -mFallSpeed * dt, 0 } );
    }
    else if ( onGround() && !isJumping )
    {
        setPosition ( { getPosition().x, groundHeight, getPosition().z } );
    }
}
