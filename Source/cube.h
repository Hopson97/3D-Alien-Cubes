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
    using VboList = std::vector<GLuint*>;

    public:
        Cube    ( const glm::vec3& positionVector, const bool floats );

        ~Cube   ();

        void
        update  ( glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window, const float time ) override;

    private:
        void
        draw    ( const glm::mat4& view, const glm::mat4& proj, const float time );

    private:
        VboList     mBufferObjectList;

        GLuint      mVao;
        GLuint      mNumIndices;

        Shader      mShader;

        bool        doesFloat;

        float       mPermYPos; //Where the floaters float around
};

#endif // CUBE_H
