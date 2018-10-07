#include "mesh_component.h"


MeshComponent::MeshComponent(Shader shader, unsigned int VAO, unsigned int drawCount, bool useIndices)
    : mShader{shader}, mVAO{VAO}, mDrawCount{drawCount}, mUseIndices{useIndices}
{

}

