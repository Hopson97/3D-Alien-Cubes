#include "cube.h"

#include "opengl_funcs.h"
#include "vectors.h"
#include "rand.h"

Cube :: Cube( const glm::vec3& positionVector, const bool floats )
    :   doesFloat       ( floats )
{
    setPosition ( positionVector );

    mPermPos.y = positionVector.y;
    mPermPos.x = positionVector.x;
}

void
Cube :: update  ( glm::mat4& pvMat, sf::RenderWindow& window, const float time, const GLuint shaderID, const float dt )
{
    if ( doesFloat )
    {
        const static float multiplier = 3;
        float change = ( ( sin ( getPosition().z + getPosition().x + time ) ) / multiplier ) * dt;
        changePosition ( { 0, change, 0 } );
    }

    glm::mat4 model;

    //Translation
    model = glm::translate( model, getPosition() );

    //Rotation
    glm::mat4 xRotMat;
    glm::mat4 yRotMat;
    glm::mat4 zRotMat;

    xRotMat = glm::rotate ( xRotMat, glm::radians( getRotation().x  ), glm::vec3(1, 0, 0) );
    yRotMat = glm::rotate ( yRotMat, glm::radians( getRotation().y  ), glm::vec3(0, 1, 0) );
    zRotMat = glm::rotate ( zRotMat, glm::radians( getRotation().z  ), glm::vec3(0, 0, 1) );


    glm::mat4 rotMat;
    rotMat = xRotMat * yRotMat * zRotMat;

    //Scale
    glm::mat4 scaleMat;
    scaleMat = glm::scale(scaleMat, getScale() );

    //Creating the final matrix
    model = model * rotMat * scaleMat;

    //Shaders
    GLuint pvLoc        = glGetUniformLocation ( shaderID, "pvMat");
    GLuint modelLoc     = glGetUniformLocation ( shaderID, "modelMatrix" );
    GLuint timeLoc      = glGetUniformLocation ( shaderID, "time" );

    glUniformMatrix4fv  ( modelLoc, 1, GL_FALSE, glm::value_ptr ( model ) );
    glUniformMatrix4fv  ( pvLoc,  1, GL_FALSE, glm::value_ptr   ( pvMat ) );
    glUniform1f         ( timeLoc, time);
}












