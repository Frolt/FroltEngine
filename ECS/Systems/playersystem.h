#ifndef PLAYERSYSTEM_H
#define PLAYERSYSTEM_H

#include "ECS/system.h"

class playerSystem : public System
{
public:
    playerSystem();

    void beginPlay() override;
    void update(float deltaTime) override;
    void processInput(const InputComponent &input, MovementComponent &movement, float deltaTime) const;
};

#endif // PLAYERSYSTEM_H
