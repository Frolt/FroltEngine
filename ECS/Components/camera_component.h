#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "ECS/component.h"
#include "a_math.h"
#include "shader.h"

struct CameraComponent : public Component<CameraComponent>
{
    CameraComponent();
    CameraComponent(Shader shader);

    am::Mat4 mView;
    Shader mShader;
    bool mActive{false};
};

#endif // CAMERA_COMPONENT_H
