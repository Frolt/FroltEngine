#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "a_math.h"
#include "shader.h"


struct CameraComponent
{
    CameraComponent() = default;
    ~CameraComponent() = default;
    CameraComponent(Shader shader);

    Shader mShader;
    bool mActive{false};
    am::Mat4 view;
};

#endif // CAMERA_COMPONENT_H
