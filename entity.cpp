#include "entity.h"
#include "inputcomponent.h"

Entity::Entity(std::shared_ptr<InputComponent> inputComponent)
    : mInputComponent{inputComponent}
{
}

Entity::~Entity()
{

}

void Entity::update()
{
    mInputComponent->update();
}
