#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
:   programId       (0)
,   vertexShaderId  (0)
,   fragmentShaderId(0)
{
    setUpShader(vertexFilePath, fragmentFilePath);
}

Shader::Shader()
:   programId       (0)
,   vertexShaderId  (0)
,   fragmentShaderId(0)
{

}

void Shader::setUpShader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
    std::string vertexSource =      getShaderSource(vertexFilePath);
    std::string fragmentSource =    getShaderSource(fragmentFilePath);

    compileShader(vertexSource,     vertexShaderId,     GL_VERTEX_SHADER,   "Vertex Shader"     );
    compileShader(fragmentSource,   fragmentShaderId,   GL_FRAGMENT_SHADER, "Fragment Shader"   );

    linkShaders();
}

void Shader::useProgram()
{
    glUseProgram(programId);
}

std::string Shader::getShaderSource(const std::string& filePath)
{
    std::ifstream file;
    file.exceptions(std::ifstream::badbit);
    file.open(filePath);
    if(!file.is_open()) std::cerr << filePath << " does not exist! \n";

    std::stringstream fileBuff;
    fileBuff << file.rdbuf();

    file.close();

    std::string source = fileBuff.str();

    return source.c_str();
}

void Shader::compileShader(const std::string& sourceCode, GLuint& shaderId, const GLenum shaderType, const std::string& type )
{
    const char* sourceCodeChar = sourceCode.c_str();
    shaderId = glCreateShader(shaderType);

    glShaderSource  (shaderId, 1, &sourceCodeChar, NULL);
    glCompileShader (shaderId);

    getErrorLog(shaderId, GL_COMPILE_STATUS, type);
}

void Shader::linkShaders()
{
    programId = glCreateProgram();

    glAttachShader( programId, vertexShaderId);
    glAttachShader( programId, fragmentShaderId);
    glLinkProgram ( programId);

    getErrorLog(programId, GL_LINK_STATUS, "Linking error");

    glDetachShader(programId, vertexShaderId);
 	glDetachShader(programId, fragmentShaderId);
}

void Shader::getErrorLog(const GLuint id, const GLenum errorType, const std::string& errorTypeString)
{
    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(id, errorType, &success);

    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);            // Generate error as infoLog
        std::cout << "Error of type \" " << errorTypeString << "\" " << infoLog << std::endl;  // Display
    }
}

GLuint Shader::getProgramId() const
{
    return programId;
}

Shader::~Shader()
{
    glDeleteShader(vertexShaderId);
 	glDeleteShader(fragmentShaderId);
 	glDeleteProgram(programId);
}

void Shader::unuseProgram()
{
     glUseProgram(0);
}
/*
void Shader::loadUniformFloat(const GLuint location, const float aFloat)
{
    glUniform1f(location, aFloat);
}

void Shader::loadUniformMatrix(const GLuint location, const glm::mat4& matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::getUniformLocations() {}

*/
