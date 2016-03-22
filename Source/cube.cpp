#include "cube.h"

#include "opengl_funcs.h"
#include "vectors.h"

Cube :: Cube( const glm::vec3& vec )
:   shader  ( "Shaders/vert.vert", "Shaders/frag.frag")
,   pos     ( vec )
{
    this->indices = vectors::indices.size();

    glGenVertexArrays ( 1, &mVao);

    glBindVertexArray   ( mVao);

    glFuncs::addBufferObject    (mBufferObjectList, vectors::vertices, GL_ARRAY_BUFFER);
    glFuncs::addAttribPointer   (0, 3);

    glFuncs::addBufferObject    (mBufferObjectList, vectors::indices, GL_ELEMENT_ARRAY_BUFFER);   //Add EBO

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Cube :: ~Cube()
{
    for ( auto& vbo : mBufferObjectList ) {
        glDeleteBuffers (1, vbo);
    }
    glDeleteVertexArrays ( 1, &mVao);
}

void
Cube :: update  ( const glm::mat4& view, const glm::mat4& proj, const float time )
{
    draw ( view, proj, time );
}

void
Cube :: draw    ( const glm::mat4& view, const glm::mat4& proj, const float time )
{
    glBindVertexArray ( mVao );
    shader.useProgram();

    glm::mat4 model;
    model = glm::translate( model, pos);

    glm::mat4 xRotMat;
    glm::mat4 yRotMat;
    glm::mat4 zRotMat;

    xRotMat = glm::rotate ( xRotMat, glm::radians( xRot ), glm::vec3(1, 0, 0) );
    yRotMat = glm::rotate ( yRotMat, glm::radians( yRot ), glm::vec3(0, 1, 0) );
    zRotMat = glm::rotate ( zRotMat, glm::radians( zRot ), glm::vec3(0, 0, 1) );

    glm::mat4 rotMat;
    rotMat = xRotMat * yRotMat * zRotMat;

    model = model * rotMat;

    GLuint projLoc      = glGetUniformLocation(shader.getProgramId(), "projectionMatrix");  //Don't forget to write this stuff
    GLuint viewLoc      = glGetUniformLocation(shader.getProgramId(), "viewMatrix");        //up in the vertex SHADER
    GLuint modelLoc     = glGetUniformLocation(shader.getProgramId(), "modelMatrix");
    GLuint timeLoc      = glGetUniformLocation(shader.getProgramId(), "t");

    glUniformMatrix4fv  ( modelLoc, 1, GL_FALSE, glm::value_ptr ( model ) );
    glUniformMatrix4fv  ( viewLoc,  1, GL_FALSE, glm::value_ptr ( view  ) );
    glUniformMatrix4fv  ( projLoc,  1, GL_FALSE, glm::value_ptr ( proj  ) );
    glUniform1f         ( timeLoc, time);

    glDrawElements ( GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);


    shader.unuseProgram();
    glBindVertexArray ( 0 );
}














