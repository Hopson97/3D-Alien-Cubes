#ifndef OPENGL_FUNCTIONS_H_INCLUDED
#define OPENGL_FUNCTIONS_H_INCLUDED

#include <vector>
#include <iostream>

#include <GL/glew.h>

namespace glFuncs {

template<typename t>
void addBufferObject(std::vector<GLuint>& bufferObjectList, const std::vector<t>& data, const GLenum BUFFER_TYPE)
{
    GLuint bufferObject;
    glGenBuffers(1, &bufferObject);

    glBindBuffer(BUFFER_TYPE, bufferObject);
    glBufferData(BUFFER_TYPE, sizeof(t) * data.size(),
                 data.data(), GL_STATIC_DRAW);

    bufferObjectList.push_back(bufferObject);
}

void addAttribPointer(GLuint location, GLuint dimensionPerVertex);

GLuint createTexture(const std::string& texturePath);

}

#endif // OPENGL_FUNCTIONS_H_INCLUDED//umm, can i try something? go for it
