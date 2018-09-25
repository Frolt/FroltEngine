#ifndef COMPONENT_H
#define COMPONENT_H

#include <utility>
#include "wrappers.h"

// COMPONENT COUNTER
struct ComponentCounter {
  static int counter;
};
int ComponentCounter::counter = 0;

// COMPONENT INTERFACE
template<typename T>
struct Component
{
    // Get the family for the component
    static inline int family()
    {
      static int family = ComponentCounter::counter++;
      return family;
    }
};

// STATIC METHOD FOR GETTING COMPONENT FAMILIY
template <typename C>
static int GetComponentFamily() {
  return Component<typename std::remove_const<C>::type>::family();
}

#endif // COMPONENT_H
