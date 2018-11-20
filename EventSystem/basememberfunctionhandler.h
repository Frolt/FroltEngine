#ifndef BASEMEMBERFUNCTIONHANDLER_H
#define BASEMEMBERFUNCTIONHANDLER_H

#include <memory>

// Forward declarations
struct Event;

class BaseMemberFunctionHandler
{
public:
    virtual ~BaseMemberFunctionHandler() = default;
    virtual void call(std::unique_ptr<Event> event) = 0;
};

#endif // BASEMEMBERFUNCTIONHANDLER_H
