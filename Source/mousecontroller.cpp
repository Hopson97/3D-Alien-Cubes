#include "mousecontroller.h"


void
MouseController :: getRot ( glm::vec3& rotVector, sf::RenderWindow& window )
{
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Q ) ) isMovementOn = false;
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::E ) ) isMovementOn = true;

    if ( isMovementOn )
    {
        yRot( rotVector.y, window ); // Left - Right movement
        xRot( rotVector.x, window ); // Up - Down movement
    }
}

/// /////////////////////////////////////////////////////////
///Left and Right movement ( rotation around the Y-Axis ) ///
void
MouseController :: yRot    ( float& rotY, sf::RenderWindow& window  )
{
    float rot = sf::Mouse::getPosition( window ).x - mouseXBefore;  //Remember, the X axis goes left to right, so can only rotate "up and down"

    rotY += rotChange ( rot );

    if ( rotY <= -360 ) rotY = 0;
    if ( rotY >= 360  ) rotY = 0;

    mouseXBefore = sf::Mouse::getPosition( window ).x;
}

/// //////////////////////////////////////////////////////
///Up and Down movement ( rotation around the X-Axis ) ///
void
MouseController :: xRot    ( float& rotX, sf::RenderWindow& window  )
{
    const int maxRotDown = 90;
    const int maxRotUp = -100;

    if ( rotX <= -360 ) rotX = 0;
    if ( rotX >= 360  ) rotX = 0;

    float rot = sf::Mouse::getPosition( window ).y - mouseYBefore;  //Remember, the Y axis goes up to down, so can only rotate "left and right"

    rotX += rotChange ( rot );

    mouseYBefore = sf::Mouse::getPosition( window ).y;

    if ( rotX > maxRotDown )        //Some if-statements to stop the view going upside-down
    {
        rotX = maxRotDown;
        return;
    }
    else if ( rotX < maxRotUp )
    {
        rotX = maxRotUp;
        return;
    }
}

const float
MouseController :: rotChange ( const float rot )
{
    return rot / ( MAX_SENSITIVITY - SENSITIVITY );
}
