#ifndef MODEL_H
#define MODEL_H

//For now this is only for a cube model, due to change in the future

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <glm/basics.hpp>
#include <cmath>
#include <iostream>

#include "shader.h"
#include "opengl_funcs.h"
#include "entity.h"

class Model
{
    using VboList = std::vector<GLuint>;
    public:
        Model();
        virtual ~Model();

        void
        bind    ();

        void
        unBind  ();

        const inline GLuint
        getIndexCount       () { return mNumIndices; }

        const inline GLuint
        getShaderID         () { return mShader.getProgramId(); }

        const inline GLuint
        getTexture          () { return texture; }

    private:
        VboList     mBufferObjectList;

        GLuint      texture;

        GLuint      mVao;
        GLuint      mNumIndices;

        Shader      mShader;
};

#endif // MODEL_H
