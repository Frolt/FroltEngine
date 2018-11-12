#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <list>
#include <map>
#include <typeindex>
#include "handlerfunctionbase.h"
#include "memberfunctionhandler.h"

//typedef std::list<HandlerFunctionBase*> HandlerList;
using HandlerList = std::list<HandlerFunctionBase*>;

class EventBus
{
public:
    template<typename EventType>
    void publish(EventType * evnt);

    template<class T, class EventType>
    void subscribe(T * instance, void (T::*memberFunction)(EventType *));

private:
    std::map<std::type_index, HandlerList*> subscribers;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<typename EventType>
void EventBus::publish(EventType *evnt)
{
    HandlerList * handlers = subscribers[typeid(EventType)];

    if (handlers == nullptr) {
        return;
    }

    for (auto & handler : *handlers) {
        if (handler != nullptr) {
            handler->exec(evnt);
        }
    }
}

template<class T, class EventType>
void EventBus::subscribe(T *instance, void (T::*memberFunction)(EventType *))
{
    HandlerList * handlers = subscribers[typeid(EventType)];

    //First time initialization
    if (handlers == nullptr) {
        handlers = new HandlerList();
        subscribers[typeid(EventType)] = handlers;
    }

    handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
}

#endif // EVENTBUS_H
