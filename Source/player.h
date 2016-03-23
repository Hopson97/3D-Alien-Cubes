#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h>
#include <glm/basics.hpp>
#include <SFML/Graphics.hpp>

#include "mousecontroller.h"


class Player
{
    public:
        void
        update      ( glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window );

    private:
        void
        input       ( sf::RenderWindow& window );

        void
        mouseInput  ( sf::RenderWindow& window );

        void
        walkInput   ();

        void
        jumpInput   ();

        void
        fovInput    ();

    private:
        glm::vec3 mVelocity { 0, 0, 0 };
        glm::vec3 mPosition { 0, 0, 0 };
        glm::vec3 mRotation { 0, 0, 0 };

        MouseController mMouseController;

        float mForwardSpeed = 0;
        float mMaxSpeed     = 0.21;

        float mJumpSpeed    = 0.3;
        float mFallSpeed    = 0.015;

        int     FOV_CHANGE  = 2;
        float   FOV         = 90.0f;

};

#endif // PLAYER_H
