#ifndef COMPONENT_H
#define COMPONENT_H

#include <utility>

// Counter wrapper
struct ComponentCounter {
  static unsigned int counter;
};

// Interface for components
template<typename T>
struct Component
{
protected:
    Component() = default;
public:
    static unsigned int family();
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<typename T>
unsigned int Component<T>::family()
{
    // id will only initialize once
    static unsigned int id = ComponentCounter::counter++;
    return id;
}

// TODO Not using atm
// Static method for getting component type id
template <typename T>
static unsigned int getComponentFamily() {
  return Component<T>::family();
}

#endif // COMPONENT_H
