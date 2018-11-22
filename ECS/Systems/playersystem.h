#ifndef PLAYERSYSTEM_H
#define PLAYERSYSTEM_H

#include "ECS/system.h"

/**
   @brief The playerSystem class implements player movement throught W,A,S,D input,
    and adds friction and max speed
 */
class playerSystem : public System
{
public:
    playerSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void movePlayer(const InputComponent &input, MovementComponent &movement, float deltaTime) const;
};

#endif // PLAYERSYSTEM_H
