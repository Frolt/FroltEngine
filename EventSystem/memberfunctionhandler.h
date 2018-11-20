#ifndef MEMBERFUNCTIONHANDLER_H
#define MEMBERFUNCTIONHANDLER_H

#include "basememberfunctionhandler.h"

template<class ClassInstance, class EventType>
class MemberFunctionHandler : public BaseMemberFunctionHandler
{
public:
    // Function pointer type alias
    using MemberFunction = void(ClassInstance::*)(EventType *);

    MemberFunctionHandler(ClassInstance *instance, MemberFunction memberFunction);

    void call(std::unique_ptr<Event> event) override;

  private:
    // Pointer to class instance
    ClassInstance *mInstance;
    // Pointer to member function
    MemberFunction mMemberFunction;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<class T, class EventType>
MemberFunctionHandler<T, EventType>::MemberFunctionHandler(T *instance, MemberFunction memberFunction)
    : mInstance{instance}, mMemberFunction{memberFunction}
{
}

template<class T, class EventType>
void MemberFunctionHandler<T, EventType>::call(std::unique_ptr<Event> event)
{
    // Cast event to the correct EventType, and call the member function pointer from the class instance
    (mInstance->*mMemberFunction)(static_cast<EventType *>(event.get()));
}

#endif // MEMBERFUNCTIONHANDLER_H
