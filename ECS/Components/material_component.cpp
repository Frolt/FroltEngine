#include "material_component.h"


MaterialComponent::MaterialComponent(const am::Vec3 &diffColor, const am::Vec3 &specColor, float shininess)
    : mDiffuseColor{diffColor}, mSpecularColor{specColor}, mShininess{shininess}
{

}
