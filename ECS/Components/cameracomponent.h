#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

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

#endif // CAMERACOMPONENT_H
