#ifndef MATERIAL_H
#define MATERIAL_H

#include "a_math.h"
#include "texture.h"
#include <memory>

class Material
{
public:
    Material();

    void setDiffuseMap(Texture *texture);
    void setDiffuseColor(const am::Vec& color);
    void setSpecularMap(Texture *texture);
    void setSpecularColor(const am::Vec& color);
    void setEmissionMap(Texture *texture);
    void setShininess(float value);

    Texture *getDiffuseMap();
    am::Vec3 getDiffuseColor();
    Texture *getSpecularMap();
    am::Vec3 getSpecularColor();
    Texture *getEmissionMap();
    float getShininess();
    bool hasDiffMap();
    bool hasSpecMap();
    bool hasEmissionMap();


private:
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

#endif // MATERIAL_H
