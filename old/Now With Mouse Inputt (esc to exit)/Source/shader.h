#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>
#include <glm/glm_basics.h>

class Shader
{
    public:
        Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
        Shader();
        ~Shader();

        void        setUpShader         (const std::string& vertexFilePath, const std::string& fragmentFilePath);

        GLuint      getProgramId        () const;

        void        useProgram          ();
        void        unuseProgram        ();

    protected:
        //void        loadUniformFloat    (const GLuint location, const float aFloat);
        //void        loadUniformMatrix   (const GLuint location, const glm::mat4& matrix);


    private:
        GLuint programId;
        GLuint vertexShaderId;
        GLuint fragmentShaderId;

    private:
        std::string getShaderSource     (const std::string& filePath);
        void        compileShader       (const std::string& sourceCode, GLuint& shaderId,
                                         const GLenum shaderType, const std::string& type);

        void        linkShaders         ();

        void        getErrorLog         (const GLuint id, const GLenum errorType, const std::string& errorTypeString);

    private:
        //virtual     void    getUniformLocations() = 0;




};

#endif // SHADER_H
