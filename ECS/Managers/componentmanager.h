#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <unordered_map>
#include <map>
#include <vector>
#include <functional>
#include <QtGlobal>
#include <QDebug>
#include "ECS/entity.h"
#include "ECS/Managers/basecomponentmanager.h"

// Generic component manager
template <typename T>
class ComponentManager : public BaseComponentManager
{
public:
    ComponentManager(std::size_t size = 100000);
    void addComponent(const Entity &entity, const T &component);
    void destroyComponent(const Entity &entity);
    T *getComponent(const Entity &entity);
    void iterateAll(std::function<void(T component)> lambda);

private:
    std::unordered_map<Entity, unsigned int> mEntityMap;
    unsigned int mSize{0};
    std::vector<T> mComponents;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<typename T>
ComponentManager<T>::ComponentManager(std::size_t size)
{
    mComponents.resize(size);
}

template<typename T>
void ComponentManager<T>::addComponent(const Entity &entity, const T &component)
{
    unsigned int newIndex{mSize};
    auto check = mEntityMap.insert(std::make_pair(entity, newIndex));
    // Crashes program if key aldready exist
    Q_ASSERT_X(check.second, "COMPONENTMANAGER::ADDCOMPONENT", "KEY ALREADY EXIST");
    mComponents[newIndex] = component;
    mSize++;
}

template<typename T>
void ComponentManager<T>::destroyComponent(const Entity &entity)
{
    auto index = mEntityMap.at(entity);
    mComponents[index] = mComponents[--mSize];
    mEntityMap.erase(entity);
}

template<typename T>
T *ComponentManager<T>::getComponent(const Entity &entity)
{
    auto index = mEntityMap.at(entity);
    return &mComponents[index];
}

template<typename T>
void ComponentManager<T>::iterateAll(std::function<void(T component)> lambda)
{
    for(unsigned int i = 0; i < mComponents.size; i++)
        lambda(mComponents.data[i]);
}

#endif // COMPONENTMANAGER_H
