#ifndef BASEMEMBERFUNCTIONHANDLER_H
#define BASEMEMBERFUNCTIONHANDLER_H

// Forward declarations
struct Event;

class BaseMemberFunctionHandler
{
public:
    virtual void call(Event * event) = 0;
};

#endif // BASEMEMBERFUNCTIONHANDLER_H
