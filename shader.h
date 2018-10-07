#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_4_1_Core>
#include <string>
#include "a_math.h"

class Shader
{
public:
    // Read and build vertex and fragment shader from file
    Shader() = default;
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    // Activates shader
    void use() const;
    // Sets uniform variables
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat3(const std::string &name, const am::Mat3 &mat) const;
    void setMat4(const std::string &name, const am::Mat4 &mat) const;
    void setVec3(const std::string &name, const am::Vec3 &vec) const;

    // Program ID
    unsigned int ID{0};
    QOpenGLFunctions_4_1_Core *gl = new QOpenGLFunctions_4_1_Core;
};

#endif // SHADER_H
