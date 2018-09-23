#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <array>

// Wrapper for array index
struct ComponentInstance
{
    ComponentInstance(unsigned int index) : mIndex{index} {}
    unsigned int mIndex;
};

// Wrapper for fixed array
template<typename T>
struct ComponentData
{
    unsigned int size = 1;
    std::array<T, 1024> data;
};

// COMPONENT COUNTER
struct ComponentCounter {
  static int counter;
};
int ComponentCounter::counter = 0;

#endif // WRAPPERS_H
