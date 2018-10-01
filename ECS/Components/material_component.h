#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H

#include "ECS/component.h"
#include "a_math.h"

struct MaterialComponent : public Component<MaterialComponent>
{
//    Texture *mDiffuseMap{nullptr};
//    Texture *mSpecularMap{nullptr};
//    Texture *mEmissionMap{nullptr};
    am::Vec3 mDiffuseColor{0.827f, 0.827f, 0.827f};
    am::Vec3 mSpecularColor{1};
    float mShininess{32.0f};
    bool mHasDiffMap{false};
    bool mHasSpecMap{false};
    bool mHasEmissionMap{false};
};

#endif // MATERIAL_COMPONENT_H
