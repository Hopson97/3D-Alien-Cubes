#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

#include <SFML/Graphics.hpp>
#include <glm/basics.hpp>

class MouseController
{
    public:
        void
        getRot      ( glm::vec3& rotVector, sf::RenderWindow& window );

    private:
        void
        yRot        ( float& yRot, sf::RenderWindow& window  );

        void
        xRot        ( float& xRot, sf::RenderWindow& window  );

        const float
        rotChange   ( const float rot );

    private:
        float       mouseXBefore,
                    mouseYBefore,
                    x,
                    y;

        unsigned    SENSITIVITY     { 7 },
                    MAX_SENSITIVITY { 10 };

};

#endif // MOUSECONTROLLER_H
