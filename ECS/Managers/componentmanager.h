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
    void addComponent(EntityID entity, const T &component);
    virtual void destroyComponent(EntityID entity) override;
    T *getComponent(EntityID entity);
    bool hasComponent(EntityID entity) const;
    void iterateAll(std::function<void(T &component)> lambda);

private:
    std::unordered_map<EntityID, unsigned int> mEntityMap;
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
void ComponentManager<T>::addComponent(EntityID entity, const T &component)
{
    unsigned int newIndex{mSize};
    if (mEntityMap.find(entity) == mEntityMap.end()) {
        mEntityMap[entity] = newIndex;
        mComponents[newIndex] = component;
        mSize++;
    } else {
        qDebug() << "ERROR:: Component already exist";
    }
}

template<typename T>
void ComponentManager<T>::destroyComponent(EntityID entity)
{
    if (mEntityMap.find(entity) != mEntityMap.end()) {
        // Moves the last component into the index we want to delete
        auto index = mEntityMap.at(entity);
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
    else {
        qDebug() << "ERROR:: Trying to destroy a component the entity does not have";
    }
}

template<typename T>
T *ComponentManager<T>::getComponent(EntityID entity)
{
    auto search = mEntityMap.find(entity);
    if (search != mEntityMap.end()) {
        return &mComponents[search->second];
    } else {
        qDebug() << "ERROR:: Component not found";
        return nullptr;
    }
}

template<typename T>
bool ComponentManager<T>::hasComponent(EntityID entity) const
{
    if (mEntityMap.find(entity) != mEntityMap.end())
        return true;
    else
        return false;
}

template<typename T>
void ComponentManager<T>::iterateAll(std::function<void(T &component)> lambda)
{
    for(unsigned int i = 0; i < mComponents.size(); i++)
        lambda(mComponents[i]);
}

#endif // COMPONENTMANAGER_H
