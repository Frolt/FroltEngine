#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <unordered_map>
#include <vector>
#include <typeindex>
#include "basememberfunctionhandler.h"
#include "memberfunctionhandler.h"
#include <iostream>
#include <memory>

class EventHandler
{
public:
    template<class EventType>
    void publish(std::unique_ptr<EventType> event);

    template<class ClassInstance, class EventType>
    void subscribe(ClassInstance *instance, void(ClassInstance::*memberFunction)(EventType *));

public:
    std::unordered_map<std::type_index, std::vector<std::unique_ptr<BaseMemberFunctionHandler>>> mSubscribers;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<class EventType>
void EventHandler::publish(std::unique_ptr<EventType> event)
{
    // Get the array of memberFunctions for the specific EventType
    auto &memberFunctionArray = mSubscribers[typeid(EventType)];

    // Calls all the member functions associated with the EventType
    for (auto &memberFunction : memberFunctionArray) {
        memberFunction->call(std::move(event));
    }
}

template<class ClassInstance, class EventType>
void EventHandler::subscribe(ClassInstance *instance, void(ClassInstance::*memberFunction)(EventType *))
{
    // Get the array of memberFunctions for the specific EventType
    auto &memberFunctionArray = mSubscribers[typeid(EventType)];

    // Add the new member function
    memberFunctionArray.push_back(std::make_unique<MemberFunctionHandler<ClassInstance, EventType>>(instance, memberFunction));
}

#endif // EVENTHANDLER_H
