#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H

#include "ECS/component.h"
#include "a_math.h"

class Texture;

struct MaterialComponent : public Component<MaterialComponent>
{
    MaterialComponent() {}
    MaterialComponent(am::Vec3 diffColor, am::Vec3 specColor = {1}, float shininess = 32.0f)
        : mDiffuseColor{diffColor}, mSpecularColor{specColor}, mShininess{shininess} {}
    MaterialComponent(Texture *diffMap, Texture *specMap = nullptr, Texture *emmMap = nullptr, float shininess = 32.0f)
        : mDiffuseMap{diffMap}, mSpecularMap{specMap}, mEmissionMap{emmMap}, mShininess{shininess} {}

    Texture *mDiffuseMap{nullptr};
    Texture *mSpecularMap{nullptr};
    Texture *mEmissionMap{nullptr};
    am::Vec3 mDiffuseColor{0.827f, 0.827f, 0.827f};
    am::Vec3 mSpecularColor{1};
    float mShininess{32.0f};
    bool mHasDiffMap{false};
    bool mHasSpecMap{false};
    bool mHasEmissionMap{false};
};

#endif // MATERIAL_COMPONENT_H
