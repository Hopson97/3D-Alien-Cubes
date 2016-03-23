#include "player.h"

#include "window.h"

void
Player :: update      ( glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window )
{
    if ( pos.y < 0 ) vel.y += fallSpeed;
    if ( pos.y >= 0 ) pos.y = 0;

    input ( window );

    float dz = forwardSpeed * sin (  glm::radians ( rot.y ) );
    float dx = forwardSpeed * cos (  glm::radians ( rot.y ) );

    pos.x += dx;
    pos.z += dz;
    pos.y += vel.y;

    view =  glm::translate      (view,  pos);
    proj =  glm::perspective    (glm::radians(FOV), win::WINDOW_WIDTH / win::WINDOW_HEIGHT, 0.01f, 100.0f);

    glm::mat4 yRotMat;
    glm::mat4 xRotMat;

    yRotMat = glm::rotate( yRotMat, glm::radians ( rot.y + 90 ) ,   glm::vec3 ( 0, 1, 0 ) );
    xRotMat = glm::rotate( xRotMat, glm::radians ( rot.x ) ,        glm::vec3 ( 1, 0, 0 ) );

    glm::mat4 finalRot = xRotMat * yRotMat;

    proj = proj * finalRot;

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
    mouse.getRot( rot, window );
}

void
Player :: walkInput   ()
{
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::W ) ) {
        forwardSpeed = -maxSpeed;
    }
    else if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::S ) ) {
        forwardSpeed = maxSpeed;
    }
    else {
        forwardSpeed = 0;
    }
}

void
Player :: jumpInput   ()
{
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && pos.y == 0  ) {
        vel.y -= jumpSpeed;
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
