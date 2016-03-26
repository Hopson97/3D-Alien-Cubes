#include "player.h"

#include "window.h"

#include <cmath>

struct FOVdance
{
    void
    update ( float& FOV )
    {
        if ( inc ) {
            FOV += incAmount;
            if ( FOV > MAX ) inc = false;
        }
        else {
            FOV -= incAmount;
            if ( FOV < MIN ) inc = true;
        }
    }

    private:
        bool inc { true };

        constexpr
        static
        unsigned    MAX { 179 },
                    MIN { 1   };

        constexpr
        static
        float       incAmount { 0.2 };
};

FOVdance d;

void
Player :: update      (  glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window, const float time  )
{
    if ( mPosition.y < 0 ) mVelocity.y += mFallSpeed;
    if ( mPosition.y >= 0 ) mPosition.y = 0;

    input ( window );

    //d.update( FOV );

    float       dx = 0
            ,   dz = 0;

    walkInput( dx, dz );

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
    jumpInput   ();
    fovInput    ();
}

void
Player :: mouseInput  ( sf::RenderWindow& window )
{
    mMouseController.getRot( mRotation, window );
}

void
Player :: walkInput   ( float& dx, float& dz )
{
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::W ) ) {
        dz += -mMaxSpeed * sin (  glm::radians ( mRotation.y ) );
        dx += -mMaxSpeed * cos (  glm::radians ( mRotation.y ) );
    }
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::S ) ) {
        dz += mMaxSpeed * sin (  glm::radians ( mRotation.y ) );
        dx += mMaxSpeed * cos (  glm::radians ( mRotation.y ) );
    }
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::A ) ) {
        dz += -mMaxSpeed * sin (  glm::radians ( mRotation.y - 90 ) );
        dx += -mMaxSpeed * cos (  glm::radians ( mRotation.y - 90 ) );
    }
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::D ) ) {
        dz += -mMaxSpeed * sin (  glm::radians ( mRotation.y + 90 ) );
        dx += -mMaxSpeed * cos (  glm::radians ( mRotation.y + 90 ) );
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
