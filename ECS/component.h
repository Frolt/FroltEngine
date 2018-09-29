#ifndef COMPONENT_H
#define COMPONENT_H

#include <utility>

// Counter wrapper
struct ComponentCounter {
  static int counter;
};

// Interface for components
template<typename T>
struct Component
{
    static int typeID();
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<typename T>
int Component<T>::typeID()
{
    // id will only initialize once
    static int id = ComponentCounter::counter++;
    return id;
}

// Static method for getting component type id
template <typename T>
static int getComponentTypeID() {
  return Component<T>::typeID();
}

#endif // COMPONENT_H
