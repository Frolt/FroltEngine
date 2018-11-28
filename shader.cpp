#include "shader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    gl->initializeOpenGLFunctions();

    // ----------------------------------------------------------------
    // Reading GLSL code from file
    // ----------------------------------------------------------------
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        vShaderFile.open(vertexPath.c_str());
        fShaderFile.open(fragmentPath.c_str());
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        qWarning() << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ >> " << vertexPath.c_str() << " >> " << fragmentPath.c_str();
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // ----------------------------------------------------------------
    // Shaders and Program
    // ----------------------------------------------------------------
    gl->initializeOpenGLFunctions();

    int success;
    char infoLog[512];
    unsigned int vertexShader = gl->glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = gl->glCreateShader(GL_FRAGMENT_SHADER);
    // Vertex shader
    gl->glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    gl->glCompileShader(vertexShader);
    // Check for compiler error
    gl->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        gl->glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        qWarning() << "ERROR::SHADER::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog;
    }
    // Fragment shader
    gl->glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    gl->glCompileShader(fragmentShader);
    // Check for compiler error
    gl->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        gl->glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        qWarning() << "ERROR::SHADER::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog;
    }
    // Program
    ID = gl->glCreateProgram();
    gl->glAttachShader(ID, vertexShader);
    gl->glAttachShader(ID, fragmentShader);
    gl->glLinkProgram(ID);
    gl->glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        gl->glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        qWarning() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
    }
    // Deleting shaders
    gl->glDeleteShader(vertexShader);
    gl->glDeleteShader(fragmentShader);
    // ----------------------------------------------------------------
}

void Shader::use() const
{
    gl->glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    gl->glUniform1i(gl->glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string &name, int value) const
{
    gl->glUniform1i(gl->glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    gl->glUniform1f(gl->glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, const am::Vec3 &vec) const
{
    gl->glUniform3fv(gl->glGetUniformLocation(ID, name.c_str()), 1, vec.data());
}

void Shader::setMat3(const std::string &name, const am::Mat3 &mat) const
{
    gl->glUniformMatrix3fv(gl->glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, mat.data());
}

void Shader::setMat4(const std::string &name, const am::Mat4 &mat) const
{
    gl->glUniformMatrix4fv(gl->glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, mat.data());
}
