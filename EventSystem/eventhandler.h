#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include "basememberfunctionhandler.h"
#include "memberfunctionhandler.h"

/**
   @brief The EventHandler class is the central event system in the engine.
   it saves member function pointers to all systems that has subscribed to a specific Event
 */
class EventHandler
{
public:
    /// When an event is published, all the systems that has subscribed to that event will have it's specified member function called
    template<class EventType>
    void publish(std::unique_ptr<EventType> event);

    /// A system that has subsribed to a specific event will recieve all the published instances of that Event
    template<class ClassInstance, class EventType>
    void subscribe(ClassInstance *instance, void(ClassInstance::*memberFunction)(EventType *));

private:
    /**
    @brief mSubscribers Type index can be used to get a unique number from each type in the engine.
        This typeindex is used as an hash key to identify each vector of memberfunction pointers
    */
    std::unordered_map<std::type_index, std::vector<std::unique_ptr<BaseMemberFunctionHandler>>> mSubscribers;
};

//--------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------------

template<class EventType>
void EventHandler::publish(std::unique_ptr<EventType> event)
{
    // Get the array of memberFunctions for the specific EventType
    auto &memberFunctionArray = mSubscribers[typeid (EventType)];

    // Calls all the member functions associated with the EventType
    for (auto &memberFunction : memberFunctionArray) {
        memberFunction->call(std::move(event));
    }
}

template<class ClassInstance, class EventType>
void EventHandler::subscribe(ClassInstance *instance, void(ClassInstance::*memberFunction)(EventType *))
{
    // Get the array of memberFunctions for the specific EventType
    auto &memberFunctionArray = mSubscribers[typeid (EventType)];

    // Add the new member function
    memberFunctionArray.push_back(std::make_unique<MemberFunctionHandler<ClassInstance, EventType>>(instance, memberFunction));
}

#endif // EVENTHANDLER_H
