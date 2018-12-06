#ifndef BASEMEMBERFUNCTIONHANDLER_H
#define BASEMEMBERFUNCTIONHANDLER_H

#include <memory>


// Forward declarations
struct Event;

/**
   @brief The BaseMemberFunctionHandler class is a simple interface for the MemberFunctionHandler class.
   it has a purte virtual call function that takes an Event that will MemberFunctionHandler will cast to the appropriate Event
 */
class BaseMemberFunctionHandler
{
public:
    virtual ~BaseMemberFunctionHandler() = default;
    virtual void call(std::unique_ptr<Event> event) = 0;
};

#endif // BASEMEMBERFUNCTIONHANDLER_H
