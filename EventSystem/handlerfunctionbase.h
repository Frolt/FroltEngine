#ifndef HANDLERFUNCTIONBASE_H
#define HANDLERFUNCTIONBASE_H

// Forward declarations
class Event;

class HandlerFunctionBase
{
public:
    // Call the member function
    void exec(Event * evnt);
private:
    // Implemented by MemberFunctionHandler
    virtual void call(Event * event) = 0;

};

#endif // HANDLERFUNCTIONBASE_H
