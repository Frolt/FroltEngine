#include "terrainsystem.h"

TerrainSystem::TerrainSystem()
{
    mSystemMask.addComponent<TerrainComponent>();
}

void TerrainSystem::beginPlay()
{
    for (auto entity : mRegisteredEntities) {
        ComponentHandle<TerrainComponent> terrain;
        ComponentHandle<TransformComponent> transform;
        mWorld->unpack(entity, terrain, transform);
        applyTransformation(terrain, transform);
    }
}

void TerrainSystem::update(float )
{
    for (auto entity : mRegisteredEntities) {
        ComponentHandle<TerrainComponent> terrain;
        ComponentHandle<TransformComponent> transform;
        mWorld->unpack(entity, terrain, transform);
        if (terrain().mStatic == false)
            applyTransformation(terrain, transform);
    }
}

void TerrainSystem::applyTransformation(TerrainComponent &terrain, TransformComponent &transform)
{
    // Matrix transformation happens in reverse order
    //---------------------------------------------------------------------------------
    am::Mat4 modelMatrix;
    modelMatrix.translate(transform.mPosition);
    modelMatrix.rotate(transform.mEulerAngles.yaw(), am::up());
    modelMatrix.rotate(transform.mEulerAngles.pitch(), am::right());
    modelMatrix.rotate(transform.mEulerAngles.roll(), am::forward());
    modelMatrix.scale(transform.mScale);

    for (auto vertex : terrain.mVertices) {
        vertex.mPosition = modelMatrix * vertex.mPosition;
    }
}
