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
template <typename ComponentType>
class ComponentManager : public BaseComponentManager
{
public:
    ComponentManager(std::size_t size = 1e5);
    void addComponent(EntityID entity, const ComponentType &component);
    virtual void destroyComponent(EntityID entity) override;
    ComponentType *getComponent(EntityID entity);
    bool hasComponent(EntityID entity) const;
    void iterateAll(std::function<void(ComponentType &component)> lambda);

private:
    std::unordered_map<EntityID, unsigned int> mEntityMap;
    unsigned int mSize{0};
    std::vector<ComponentType> mComponents;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<typename ComponentType>
ComponentManager<ComponentType>::ComponentManager(std::size_t size)
{
    mComponents.resize(size);
}

template<typename ComponentType>
void ComponentManager<ComponentType>::addComponent(EntityID entity, const ComponentType &component)
{
    auto search = mEntityMap.find(entity);
    if (search == mEntityMap.end()) {
        mEntityMap[entity] = mSize;
        mComponents[mSize++] = component;
    } else {
        qDebug() << "WARNING:: Component already exist";
    }
}

template<typename ComponentType>
void ComponentManager<ComponentType>::destroyComponent(EntityID entity)
{
    auto search = mEntityMap.find(entity);
    if (search != mEntityMap.end()) {
        // Moves the last component into the index we want to delete
        auto index = search->second;
        mComponents[index] = std::move(mComponents[--mSize]);
        mEntityMap.erase(entity);

        // Find the key that pointed to the last component and redirect it to the new index
        for (auto &element : mEntityMap) {
            if (element.second == mSize) {
                element.second = index;
                break;
            }
        }
    }
//    else {
//        qDebug() << "WARNING:: Trying to destroy a component the entity does not have";
//    }
}

template<typename ComponentType>
ComponentType *ComponentManager<ComponentType>::getComponent(EntityID entity)
{
    auto search = mEntityMap.find(entity);
    if (search != mEntityMap.end()) {
        return &mComponents[search->second];
    } else {
        qDebug() << "WARNING:: Component not found";
        return nullptr;
    }
}

template<typename ComponentType>
bool ComponentManager<ComponentType>::hasComponent(EntityID entity) const
{
    if (mEntityMap.find(entity) != mEntityMap.end())
        return true;
    else
        return false;
}

template<typename ComponentType>
void ComponentManager<ComponentType>::iterateAll(std::function<void(ComponentType &component)> lambda)
{
    for (unsigned int i = 0; i < mComponents.size(); i++)
        lambda(mComponents[i]);
}

#endif // COMPONENTMANAGER_H
