#include "mousecontroller.h"


void
MouseController :: getRot ( glm::vec3& rotVector )
{
    yRot( rotVector.y );
    xRot( rotVector.x );
}

void
MouseController :: yRot ( float& rotY )
{
    float rot = sf::Mouse::getPosition().x - mouseXBefore;

    rotY += rot / ( MAX_SENSITIVITY - SENSITIVITY );

    if ( rotY <= -360 ) rotY = 0;
    if ( rotY >= 360  ) rotY = 0;

    mouseXBefore = sf::Mouse::getPosition().x;//
}

void
MouseController :: xRot ( float& rotX )
{
    const int maxRotDown = 50;
    const int maxRotUp = -100;

    if ( rotX <= -360 )  rotX = 0;
    if ( rotX >=  360  ) rotX = 0;

    if ( rotX > maxRotDown ) {
        rotX = maxRotDown - 0.1;
        return;
    }
    else if ( rotX < maxRotUp ) {
        rotX = maxRotUp + 0.1;
        return;
    }

    float rot = sf::Mouse::getPosition().y - mouseYBefore;

    rotX += rot / ( MAX_SENSITIVITY - SENSITIVITY );

    mouseYBefore = sf::Mouse::getPosition().y;
}
