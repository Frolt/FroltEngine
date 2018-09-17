#include "gameobject.h"
#include "component.h"
#include <QDebug>

GameObject::GameObject(std::vector<std::unique_ptr<Component> > &components)
    : mComponents{std::move(components)}
{
    for (auto &x : mComponents) {
        x->mOwner = this;
        x->beginPlay();
    }
}

GameObject::GameObject(std::vector<std::unique_ptr<Component> > &&components)
    : mComponents{std::move(components)}
{
    for (auto &x : mComponents) {
        x->mOwner = this;
        x->beginPlay();
    }
}

void GameObject::update(float deltaTime)
{
    for (auto &x : mComponents)
        x->update(deltaTime);
}
