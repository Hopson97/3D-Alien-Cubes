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
        glm::vec3 vel { 0, 0, 0 };
        glm::vec3 pos { 0, 0, 0 };
        glm::vec3 rot { 0, 0, 0 };

        MouseController mouse;

        float forwardSpeed = 0;
        float maxSpeed = 0.21;

        float jumpSpeed = 0.3;
        float fallSpeed = 0.015;

        int FOV_CHANGE = 2;
        float FOV = 90.0f;

};

#endif // PLAYER_H
