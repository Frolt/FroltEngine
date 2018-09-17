#include "factory.h"
#include "playerinputcomponent.h"
#include "transformcomponent.h"
#include "viewport.h"
#include "gameobject.h"

namespace Factory {

std::unique_ptr<GameObject> makePlayerInputComponent(Viewport *viewport)
{
    std::vector<std::unique_ptr<Component>> components;
    components.push_back(std::make_unique<PlayerInputComponent>(&viewport->mInputState));
    return std::make_unique<GameObject>(components);
}

std::unique_ptr<GameObject> makeInputAndTransform(Viewport *viewport)
{
    std::vector<std::unique_ptr<Component>> components;
    components.push_back(std::make_unique<PlayerInputComponent>(&viewport->mInputState));
    components.push_back(std::make_unique<TransformComponent>());
    return std::make_unique<GameObject>(components);
}

}
