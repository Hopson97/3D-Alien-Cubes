#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>
#include <glm/basics.hpp>
#include <SFML/Graphics.hpp>

class Entity
{
    public:
        virtual void
        update      ( glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window, const float time ) = 0;

    protected:
        glm::vec3 mVelocity { 0, 0, 0 };
        glm::vec3 mPosition { 0, 0, 0 };
        glm::vec3 mRotation { 0, 0, 0 };
};

#endif // ENTITY_H
