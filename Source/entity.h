#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>
#include <glm/basics.hpp>
#include <SFML/Graphics.hpp>

class Entity
{

    protected:
        glm::vec3 mVelocity { 0, 0, 0 };
        glm::vec3 mPosition { 0, 0, 0 };
        glm::vec3 mRotation { 0, 0, 0 };
        glm::vec3 mScale    { 1, 1, 1 };
};

#endif // ENTITY_H
