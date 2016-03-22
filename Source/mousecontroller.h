#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

#include <SFML/Graphics.hpp>
#include <glm/basics.hpp>

class MouseController
{
    public:
        void
        getRot  ( glm::vec3& rotVector );

    private:
        void
        yRot    ( float& yRot );

        void
        xRot    ( float& xRot );

    private:

        float mouseXBefore;
        float mouseYBefore;

        constexpr static unsigned      SENSITIVITY = 7;
        constexpr static unsigned  MAX_SENSITIVITY = 10;
};

#endif // MOUSECONTROLLER_H
