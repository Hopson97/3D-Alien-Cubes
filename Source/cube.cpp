#include "cube.h"

#include "opengl_funcs.h"
#include "vectors.h"
#include "rand.h"

Cube :: Cube( const glm::vec3& positionVector, const bool floats )
:   mShader         ( "Shaders/vert.vert", "Shaders/frag.frag" )
,   doesFloat       ( floats )
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

    const static std::vector<GLfloat> texture =
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

    mPosition = positionVector;

    mNumIndices = indices.size();

    glGenVertexArrays ( 1, &mVao);
    glBindVertexArray   ( mVao);

    glFuncs::addBufferObject    (mBufferObjectList, vertices, GL_ARRAY_BUFFER);
    glFuncs::addAttribPointer   (0, 3);

    glFuncs::addBufferObject    (mBufferObjectList, indices, GL_ELEMENT_ARRAY_BUFFER);   //Add EBO

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mPermPos.y = positionVector.y;
    mPermPos.x = positionVector.x;
}

Cube :: ~Cube()
{
    for ( auto& vbo : mBufferObjectList ) {
        glDeleteBuffers (1, vbo);
    }
    glDeleteVertexArrays ( 1, &mVao);
}

void
Cube :: update  ( glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window, const float time )
{
    if ( doesFloat ) {
        const static float multiplier = 2;

        mPosition.y = mPermPos.y + sin(mPosition.x + time) / multiplier;
    }
    draw ( view, proj, time );
}

void
Cube :: draw    ( const glm::mat4& view, const glm::mat4& proj, const float time )
{
    glBindVertexArray ( mVao );
    mShader.useProgram();

    glm::mat4 model;
    model = glm::translate( model, mPosition );

        //Rotation
    glm::mat4 xRotMat;
    glm::mat4 yRotMat;
    glm::mat4 zRotMat;

    xRotMat = glm::rotate ( xRotMat, glm::radians( mRotation.x  ), glm::vec3(1, 0, 0) );
    yRotMat = glm::rotate ( yRotMat, glm::radians( mRotation.y  ), glm::vec3(0, 1, 0) );
    zRotMat = glm::rotate ( zRotMat, glm::radians( mRotation.z ), glm::vec3(0, 0, 1) );


    glm::mat4 rotMat;
    rotMat = xRotMat * yRotMat * zRotMat;

    model = model * rotMat;

    //SCALE
    glm::mat4 scaleMat;
    scaleMat = glm::scale(scaleMat, mScale);
    model = model * scaleMat;

    //Shaders

    GLuint projLoc      = glGetUniformLocation ( mShader.getProgramId(), "projectionMatrix" );
    GLuint viewLoc      = glGetUniformLocation ( mShader.getProgramId(), "viewMatrix"  );
    GLuint modelLoc     = glGetUniformLocation ( mShader.getProgramId(), "modelMatrix" );
    GLuint timeLoc      = glGetUniformLocation ( mShader.getProgramId(), "time" );

    glUniformMatrix4fv  ( modelLoc, 1, GL_FALSE, glm::value_ptr ( model ) );
    glUniformMatrix4fv  ( viewLoc,  1, GL_FALSE, glm::value_ptr ( view  ) );
    glUniformMatrix4fv  ( projLoc,  1, GL_FALSE, glm::value_ptr ( proj  ) );
    glUniform1f         ( timeLoc, time);

    glDrawElements ( GL_TRIANGLES, mNumIndices, GL_UNSIGNED_INT, 0);

    //glDrawArrays( GL_TRIANGLES, 0, mNumIndices );


    mShader.unuseProgram();
    glBindVertexArray ( 0 );
}














