#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

// Forward declarations
class InputComponent;

class Entity
{
public:
    Entity(std::shared_ptr<InputComponent> inputComponent);
    virtual ~Entity();

    virtual void update();

private:
    std::shared_ptr<InputComponent> mInputComponent;
};

#endif // ENTITY_H
