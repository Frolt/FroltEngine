#ifndef MEMBERFUNCTIONHANDLER_H
#define MEMBERFUNCTIONHANDLER_H

#include "handlerfunctionbase.h"

template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase
{
public:
    typedef void (T::*MemberFunction)(EventType*);

    MemberFunctionHandler(T *instance, MemberFunction memberFunction);
    void call(Event * evnt) override;

  private:
    // Pointer to class instance
    T *mInstance;
    // Pointer to member function
    MemberFunction mMemberFunction;
};

template<class T, class EventType>
MemberFunctionHandler<T, EventType>::MemberFunctionHandler(T *instance, MemberFunction memberFunction)
    : mInstance{instance}, mMemberFunction{memberFunction}
{

}

template<class T, class EventType>
void MemberFunctionHandler<T, EventType>::call(Event *event)
{
    // Cast event to the correct type and call member function
    (mInstance->*mMemberFunction)(static_cast<EventType*>(event));
}

#endif // MEMBERFUNCTIONHANDLER_H
