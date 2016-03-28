#include "model.h"

#include "opengl_funcs.h"
#include "vectors.h"
#include "rand.h"


Model :: Model()
:   mShader ( "Shaders/vert.vert", "Shaders/frag.frag" )
{
    const static std::vector<GLfloat> vertices =
    {
				-0.5f,0.5f,-0.5f,
				-0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f,0.5f,-0.5f,

				-0.5f,0.5f,0.5f,
				-0.5f,-0.5f,0.5f,
				0.5f,-0.5f,0.5f,
				0.5f,0.5f,0.5f,

				0.5f,0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,0.5f,
				0.5f,0.5f,0.5f,

				-0.5f,0.5f,-0.5f,
				-0.5f,-0.5f,-0.5f,
				-0.5f,-0.5f,0.5f,
				-0.5f,0.5f,0.5f,

				-0.5f,0.5f,0.5f,
				-0.5f,0.5f,-0.5f,
				0.5f,0.5f,-0.5f,
				0.5f,0.5f,0.5f,

				-0.5f,-0.5f,0.5f,
				-0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,0.5f
    };

    const static std::vector<GLuint> indices =
    {
				0,1,3,
				3,1,2,
				4,5,7,
				7,5,6,
				8,9,11,
				11,9,10,
				12,13,15,
				15,13,14,
				16,17,19,
				19,17,18,
				20,21,23,
				23,21,22
    };

    const static std::vector<GLuint> textureCoords =
    {
				0,0,
				0,1,
				1,1,
				1,0,
				0,0,
				0,1,
				1,1,
				1,0,
				0,0,
				0,1,
				1,1,
				1,0,
				0,0,
				0,1,
				1,1,
				1,0,
				0,0,
				0,1,
				1,1,
				1,0,
				0,0,
				0,1,
				1,1,
				1,0
    };

    mNumIndices = indices.size();

    glGenVertexArrays ( 1, &mVao);
    glBindVertexArray   ( mVao);

    glFuncs::addBufferObject    (mBufferObjectList, vertices, GL_ARRAY_BUFFER);
    glFuncs::addAttribPointer   (0, 3);

    glFuncs::addBufferObject    (mBufferObjectList, indices, GL_ELEMENT_ARRAY_BUFFER);   //Add EBO

    glFuncs::addBufferObject    (mBufferObjectList, textureCoords, GL_TEXTURE_BUFFER);
    glFuncs::addAttribPointer   (1, 2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    texture = glFuncs::createTexture( "Images/ayy lmao.png" );

    glDisableVertexAttribArray ( 0 );
    glDisableVertexAttribArray ( 1 );
}

Model::~Model()
{
    for ( auto& vbo : mBufferObjectList ) {
        glDeleteBuffers (1, vbo);
    }
    glDeleteVertexArrays ( 1, &mVao);
}

void
Model :: bind ()
{
    glBindVertexArray ( mVao );
    mShader.useProgram();

    glBindTexture(GL_TEXTURE_2D, texture);
}

void
Model :: unBind  ()
{
    mShader.unuseProgram    ( );
    glBindVertexArray       ( 0 );
    glBindTexture           ( GL_TEXTURE_2D, 0 );
}
