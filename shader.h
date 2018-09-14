#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_4_1_Core>
#include <string>
#include "a_math.h"

class Shader : protected QOpenGLFunctions_4_1_Core
{
public:
    // Read and build vertex and fragment shader from file
    Shader(const std::string vertexPath, const std::string fragmentPath);
    // Activates shader
    void use();
    // Sets uniform variables
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setMat4(const std::string& name, const am::Mat4& mat);
    void setVec3(const std::string& name, const am::Vec3& vec);

    // Program ID
    unsigned int ID;
};

#endif // SHADER_H
