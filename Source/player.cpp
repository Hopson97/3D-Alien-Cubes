#include "player.h"

#include "window.h"

void
Player :: update      ( glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window )
{
    if ( mPosition.y < 0 ) mVelocity.y += mFallSpeed;
    if ( mPosition.y >= 0 ) mPosition.y = 0;

    input ( window );

    float dz = mForwardSpeed * sin (  glm::radians ( mRotation.y ) );
    float dx = mForwardSpeed * cos (  glm::radians ( mRotation.y ) );

    mPosition.x += dx;
    mPosition.z += dz;
    mPosition.y += mVelocity.y;

    view =  glm::translate      (view,  mPosition);
    proj =  glm::perspective    (glm::radians(FOV), win::WINDOW_WIDTH / win::WINDOW_HEIGHT, 0.01f, 100.0f);

    glm::mat4 yRotationMatrix;
    glm::mat4 xRotationMatrix;

    yRotationMatrix = glm::rotate( yRotationMatrix, glm::radians ( mRotation.y + 90 ) ,   glm::vec3 ( 0, 1, 0 ) );
    xRotationMatrix = glm::rotate( xRotationMatrix, glm::radians ( mRotation.x ) ,        glm::vec3 ( 1, 0, 0 ) );

    glm::mat4 finalmRotation = xRotationMatrix * yRotationMatrix;

    proj = proj * finalmRotation;

}

void
Player :: input       ( sf::RenderWindow& window )
{
    mouseInput  ( window );
    walkInput   ();
    jumpInput   ();
    fovInput    ();
}

void
Player :: mouseInput  ( sf::RenderWindow& window )
{
    mMouseController.getRot( mRotation, window );
}

void
Player :: walkInput   ()
{
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::W ) ) {
        mForwardSpeed = -mMaxSpeed;
    }
    else if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::S ) ) {
        mForwardSpeed = mMaxSpeed;
    }
    else {
        mForwardSpeed = 0;
    }
}

void
Player :: jumpInput   ()
{
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && mPosition.y == 0  ) {
        mVelocity.y -= mJumpSpeed;
    }
}

void
Player :: fovInput ()
{
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::P) ) {
        FOV += FOV_CHANGE;
        if ( FOV > 179 ) FOV = 179;
    }
    else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::O) ) {
        FOV -= FOV_CHANGE;
        if ( FOV < 1 ) FOV = 1;
    }
}
