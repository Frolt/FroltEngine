#ifndef PLAYERSYSTEM_H
#define PLAYERSYSTEM_H

#include "ECS/system.h"


/**
   @brief The playerSystem class implements player movement throught W,A,S,D input,
    and adds friction and max speed
 */
class PlayerSystem : public System
{
public:
    PlayerSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void movePlayer(const InputComponent &input, const TransformComponent &transform, MovementComponent &movement, float deltaTime, EntityHandle entity) const;
};

#endif // PLAYERSYSTEM_H
