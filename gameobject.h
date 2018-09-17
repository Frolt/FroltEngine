#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <vector>
#include <initializer_list>

// Forward declarations
class Component;

class GameObject
{
public:
    GameObject(std::vector<std::unique_ptr<Component> > &components);
    GameObject(std::vector<std::unique_ptr<Component> > &&components);
    void update(float deltaTime);

    template<class Type>
    Type *getComponent();


private:
    std::vector<std::unique_ptr<Component>> mComponents;
};

//--------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------

template<class Type>
Type *GameObject::getComponent()
{
    for (auto &x : mComponents)
        if (auto tmp = dynamic_cast<Type*>(x.get()))
            return tmp;
    return nullptr;
}

#endif // GAMEOBJECT_H
