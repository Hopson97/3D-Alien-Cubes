#include "cube.h"

#include "opengl_funcs.h"
#include "vectors.h"
#include "rand.h"

Cube :: Cube( const glm::vec3& positionVector, const bool floats )
:   doesFloat       ( floats )
{
    mPosition = positionVector;

    mPermPos.y = positionVector.y;
    mPermPos.x = positionVector.x;
}

void
Cube :: update  ( glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window, const float time, const GLuint shaderID, const float dt )
{
    if ( doesFloat ) {
        const static float multiplier = 2;

        mPosition.y = mPermPos.y + sin(mPosition.x + time) / multiplier;
    }

    glm::mat4 model;

    //Translation
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

    //Scale
    glm::mat4 scaleMat;
    scaleMat = glm::scale(scaleMat, mScale);

    //Creating the final matrix
    model = model * rotMat * scaleMat;

    //Shaders
    GLuint projLoc      = glGetUniformLocation ( shaderID, "projectionMatrix" );
    GLuint viewLoc      = glGetUniformLocation ( shaderID, "viewMatrix"  );
    GLuint modelLoc     = glGetUniformLocation ( shaderID, "modelMatrix" );
    GLuint timeLoc      = glGetUniformLocation ( shaderID, "time" );

    glUniformMatrix4fv  ( modelLoc, 1, GL_FALSE, glm::value_ptr ( model ) );
    glUniformMatrix4fv  ( viewLoc,  1, GL_FALSE, glm::value_ptr ( view  ) );
    glUniformMatrix4fv  ( projLoc,  1, GL_FALSE, glm::value_ptr ( proj  ) );
    glUniform1f         ( timeLoc, time);

    //glDrawElements ( GL_TRIANGLES, mNumIndices, GL_UNSIGNED_INT, 0);

    //glDrawArrays( GL_TRIANGLES, 0, mNumIndices );
}














