#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <memory>

// Forward declarations
class Component;
class Viewport;
class GameObject;

namespace Factory {

std::unique_ptr<GameObject> makePlayerInputComponent(Viewport *viewport);
std::unique_ptr<GameObject> makeInputAndTransform(Viewport *viewport);

}

#endif // FACTORY_H
