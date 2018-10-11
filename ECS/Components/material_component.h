#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H

#include "ECS/component.h"
#include "a_math.h"
#include "texture.h"

// Forward declarations
struct Texture;

struct MaterialComponent : public Component<MaterialComponent>
{
    MaterialComponent() = default;
    MaterialComponent(const am::Vec3 &diffColor, const am::Vec3 &specColor = {1}, float shininess = 32.0f);

    std::vector<Texture> mTextures;
    am::Vec3 mDiffuseColor{0.827f, 0.827f, 0.827f};
    am::Vec3 mSpecularColor{0.5};
    float mShininess{32.0f};
    bool mHasDiffMap{false};
    bool mHasSpecMap{false};
    bool mHasEmissionMap{false};
    bool mIsLight{false};
};

#endif // MATERIAL_COMPONENT_H
