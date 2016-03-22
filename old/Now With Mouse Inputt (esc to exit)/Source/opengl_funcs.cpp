#include "opengl_funcs.h"
#include <SFML/Graphics.hpp>

namespace glFuncs {

void addAttribPointer(GLuint location, GLuint dimensionPerVertex)
{
    glVertexAttribPointer(location, dimensionPerVertex, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(location);
}

GLuint createTexture(const std::string& texturePath)
{
    sf::Image image;
    image.loadFromFile(texturePath);
    image.flipVertically();

    GLuint texturevbo;
    glGenTextures(1, &texturevbo);
    glBindTexture(GL_TEXTURE_2D, texturevbo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texturevbo;
}

}
