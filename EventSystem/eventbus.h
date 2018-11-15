#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <map>
#include <vector>
#include <typeindex>
#include "basememberfunctionhandler.h"
#include "memberfunctionhandler.h"
#include <iostream>

class EventBus
{
public:
    template<class EventType>
    void publish(EventType * event);

    template<class ClassInstance, class EventType>
    void subscribe(ClassInstance *instance, void(ClassInstance::*memberFunction)(EventType *));

public:
    std::map<std::type_index, std::vector<BaseMemberFunctionHandler*>> mSubscribers;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<class EventType>
void EventBus::publish(EventType *event)
{
    // Get the array of memberFunctions for the specific EventType
    auto &memberFunctionArray = mSubscribers[typeid(EventType)];

    // Calls all the member functions associated with the EventType
    for (auto &memberFunction : memberFunctionArray) {
        memberFunction->call(event);
    }
}

template<class ClassInstance, class EventType>
void EventBus::subscribe(ClassInstance *instance, void(ClassInstance::*memberFunction)(EventType *))
{
    // Get the array of memberFunctions for the specific EventType
    auto &memberFunctionArray = mSubscribers[typeid(EventType)];

    // Add the new member function
    memberFunctionArray.push_back(new MemberFunctionHandler<ClassInstance, EventType>(instance, memberFunction));
}

#endif // EVENTBUS_H
