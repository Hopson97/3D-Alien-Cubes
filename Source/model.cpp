#include "model.h"

#include "opengl_funcs.h"
#include "vectors.h"
#include "rand.h"


Model :: Model()
:   mShader ( "Shaders/vert.vert", "Shaders/frag.frag" )
{
const static std::vector<GLfloat> vertices =
{
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,

    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,

    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,

    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f
};

const static std::vector<GLfloat> textureCoords =
{
    0,0,
    1,0,
    0,1,
    1,1,

    0,0,
    1,0,
    0,1,
    1,1,

    0,0,
    1,0,
    0,1,
    1,1,

    0,0,
    1,0,
    0,1,
    1,1,

    0,0,
    1,0,
    0,1,
    1,1,

    0,0,
    1,0,
    0,1,
    1,1
};

const static std::vector<GLuint> indices =
{
    0, 1, 2,
    2, 1, 3,
    4, 5, 6,
    6, 5, 7,
    8, 9, 10,
    10, 9, 11,
    12, 13, 14,
    14, 13, 15,
    16, 17, 18,
    18, 17, 19,
    20, 21, 22,
    22, 21, 23,
    24, 25, 26,
    26, 25, 27
};

    mNumIndices = indices.size();

    glGenVertexArrays ( 1, &mVao);
    glBindVertexArray   ( mVao);

    glFuncs::addBufferObject    (mBufferObjectList, vertices, GL_ARRAY_BUFFER);         //Vertex coordinates
    glFuncs::addAttribPointer   (0, 3);

    glFuncs::addBufferObject    (mBufferObjectList, indices, GL_ELEMENT_ARRAY_BUFFER);   //Add EBO

    glFuncs::addBufferObject    (mBufferObjectList, textureCoords, GL_ARRAY_BUFFER);  //Texture coordinates
    glFuncs::addAttribPointer   (1, 2);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    texture = glFuncs::createTexture( "Images/ayy lmao.png" );
    //texture = glFuncs::createTexture( "Images/bisqwit.png" );
}

Model::~Model()
{
    for ( auto& vbo : mBufferObjectList ) {
        glDeleteBuffers (1, &vbo);
    }
    glDeleteVertexArrays ( 1, &mVao);
}

void
Model :: bind ()
{
    glBindVertexArray ( mVao );
    mShader.useProgram();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(mShader.getProgramId(), "txr"), 0);
    //glActiveTexture(GL_TEXTURE0);
}

void
Model :: unBind  ()
{
    mShader.unuseProgram    ( );
    glBindVertexArray       ( 0 );
}
