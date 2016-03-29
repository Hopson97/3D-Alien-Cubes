#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <glm/basics.hpp>
#include <cmath>
#include <iostream>

#include "shader.h"
#include "opengl_funcs.h"
#include "entity.h"

class Cube : public Entity
{
    public:
        Cube    ( const glm::vec3& positionVector, const bool floats );

        void
        update  ( glm::mat4& pvMat, sf::RenderWindow& window, const float time, const GLuint shaderID, const float dt);

    private:
        bool        doesFloat;

        glm::vec3   mPermPos;
};

#endif // CUBE_H
