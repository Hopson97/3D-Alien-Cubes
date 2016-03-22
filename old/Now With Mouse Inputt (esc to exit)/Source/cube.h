#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <glm/glm_basics.h>
#include <cmath>
#include <iostream>

#include "shader.h"
#include "opengl_funcs.h"

class Cube
{
    public:
        Cube( const glm::vec3& vec );

        ~Cube();

        void
        update      ( const glm::mat4& view, const glm::mat4& proj );

    private:
        void
        draw        ( const glm::mat4& view, const glm::mat4& proj );

        GLuint mVao;

        std::vector<GLuint*> mBufferObjectList;

        Shader shader;

        int indices;

        float   xRot { 0 },
                yRot { 0 },
                zRot { 0 };

        glm::vec3 pos;


};

#endif // CUBE_H
