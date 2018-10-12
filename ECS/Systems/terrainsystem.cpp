#include "terrainsystem.h"

TerrainSystem::TerrainSystem()
{
    mSystemMask.addComponent<TerrainComponent>();
}

void TerrainSystem::beginPlay()
{
    ch::Terrain terrain;
    ch::Transform transform;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, terrain, transform);
        applyTransformation(terrain, transform);
    }
}

void TerrainSystem::update(float )
{
    ch::Terrain terrain;
    ch::Transform transform;
    for (auto entity : mRegisteredEntities) {
        mWorld->unpack(entity, terrain, transform);
        if (terrain().mStatic == false) {
            applyTransformation(terrain, transform);
        }
    }
}

void TerrainSystem::applyTransformation(TerrainComponent &terrain, const TransformComponent &transform)
{
    // Matrix transformation happens in reverse order
    //---------------------------------------------------------------------------------
    am::Mat4 modelMatrix;
    modelMatrix.translate(transform.mPosition);
    modelMatrix.rotate(transform.mEulerAngles.yaw(), am::up());
    modelMatrix.rotate(transform.mEulerAngles.pitch(), am::right());
    modelMatrix.rotate(transform.mEulerAngles.roll(), am::forward());
    modelMatrix.scale(transform.mScale);

    for (auto &vertex : terrain.mVertices) {
        am::Vec4 pos{vertex.mPosition};
        am::Vec4 res = modelMatrix * pos;
        vertex.mPosition = am::Vec3{res};
    }
}
