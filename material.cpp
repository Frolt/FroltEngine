#include "material.h"

Material::Material()
{

}

void Material::setDiffuseMap(Texture *texture)
{
    mDiffuseMap = texture;
    mHasDiffMap = true;
}

void Material::setDiffuseColor(const am::Vec& color)
{
    mDiffuseColor = color;
}

void Material::setSpecularMap(Texture *texture)
{
    mSpecularMap = texture;
    mHasSpecMap = true;
}

void Material::setSpecularColor(const am::Vec& color)
{
    mSpecularColor = color;
}

void Material::setEmissionMap(Texture *texture)
{
    mEmissionMap = texture;
    mHasEmissionMap = true;
}

void Material::setShininess(float value)
{
    mShininess = value;
}

Texture *Material::getDiffuseMap()
{
    return mDiffuseMap;
}

am::Vec3 Material::getDiffuseColor()
{
    return mDiffuseColor;
}

Texture *Material::getSpecularMap()
{
    return mSpecularMap;
}

am::Vec3 Material::getSpecularColor()
{
    return mSpecularColor;
}

Texture *Material::getEmissionMap()
{
    return mEmissionMap;
}

float Material::getShininess()
{
    return mShininess;
}

bool Material::hasDiffMap()
{
    return mHasDiffMap;
}

bool Material::hasSpecMap()
{
    return mHasSpecMap;
}

bool Material::hasEmissionMap()
{
    return mHasEmissionMap;
}
