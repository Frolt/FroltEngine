#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include <unordered_map>
#include <array>
#include <functional>
#include "ECS/entity.h"
#include "ECS/Managers/basecomponentmanager.h"

// Generic component manager
template <typename T>
class ComponentManager : public BaseComponentManager
{
public:
    void addComponent(Entity entity, const T &component);
    T *getComponent(Entity entity);
    void destroy(Entity entity);
    void iterateAll(std::function<void(T component)> lambda);

private:
    std::map<Entity, unsigned int> mEntityMap;
    unsigned int mSize = 1;
    std::array<T, 1024> mComponents;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<typename T>
void ComponentManager<T>::addComponent(Entity entity, const T &component)
{
    unsigned int newIndex{mSize};
    mComponents[newIndex] = component;
    mEntityMap[entity] = newIndex;
    mSize++;
}

template<typename T>
T *ComponentManager<T>::getComponent(Entity entity)
{
    auto index = mEntityMap[entity];
    if (index == 0)
        qDebug() << "ERROR::ACCESSING INDEX ZERO IN --> \"ComponentManager<" << typeid (T).name() << ">::getComponent\"";
    return &mComponents[index];
}

template<typename T>
void ComponentManager<T>::destroy(Entity entity)
{
    auto index = mEntityMap[entity];
    if (index == 0)
        qDebug() << "ERROR::ACCESSING INDEX ZERO IN --> \"ComponentManager<" << typeid (T).name() << ">::destroy\"";
    mComponents[mEntityMap[entity]] = mComponents[mSize - 1];
    mEntityMap.erase(entity);
    mSize--;

}

template<typename T>
void ComponentManager<T>::iterateAll(std::function<void(T component)> lambda)
{
    for(unsigned int i = 1; i < mComponents.size; i++)
      lambda(mComponents.data[i]);
}

#endif // COMPONENTMANAGER_H
