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

class Cube
{
    public:
        Cube( const glm::vec3& vec, const bool floats);

        ~Cube();

        void
        update      ( const glm::mat4& view, const glm::mat4& proj, const float time );

    private:
        void
        draw        ( const glm::mat4& view, const glm::mat4& proj, const float time );

        std::vector<GLuint*> mBufferObjectList;

        GLuint      mVao;

        int         indices;

        Shader      shader;

        glm::vec3   pos;


        bool        doesFloat;

        float       permYPos,
                    xRot { 0 },
                    yRot { 0 },
                    zRot { 0 };
};

#endif // CUBE_H
