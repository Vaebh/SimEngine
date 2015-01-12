#ifndef EVENT_CALLBACK_SIMENGINE
#define EVENT_CALLBACK_SIMENGINE

#include "../Foundation/Foundation.h"
#include "../Structure/GameObject.h"
#include <iostream>

// =======================================
// BASE FUNCTION CALLBACK CLASS
// =======================================
class IEventCallback
{
public:
	virtual void operator() (uint32_t inEventType, GameObject* inTarget) = 0;
};

// =======================================
// MEMBER FUNCTION CALLBACK CLASS
// =======================================
template <class ClassType>
class EventCallbackMember : public IEventCallback
{
public:
	EventCallbackMember(ClassType* inClassPointer, void (ClassType::*inEventCallbackFunc)(uint32_t, GameObject*));
	void operator() (uint32_t inEventType, GameObject* inTarget);

public:
	void (ClassType::*mEventCallbackFunc)(uint32_t, GameObject*);
	ClassType* mClassPointer;
};

template <class ClassType>
EventCallbackMember<ClassType>::EventCallbackMember(ClassType* inClassPointer, void (ClassType::*inEventCallbackFunc)(uint32_t, GameObject*)) : 
mClassPointer(inClassPointer),
mEventCallbackFunc(inEventCallbackFunc)
{
	assert(mClassPointer && mEventCallbackFunc);
}

template <class ClassType>
void EventCallbackMember<ClassType>::operator() (uint32_t inEventType, GameObject* inTarget)
{
	//std::cout << "\nMember function callback\n";
	(mClassPointer->*mEventCallbackFunc)(inEventType, inTarget);
}

// =======================================
// FREE FUNCTION CALLBACK CLASS
// =======================================
class EventCallbackFree : public IEventCallback
{
public:
	EventCallbackFree(void (*inEventCallbackFunc)(uint32_t, GameObject*));
	void operator() (uint32_t inEventType, GameObject* inTarget);

public:
	void (*mEventCallbackFunc)(uint32_t, GameObject*);
};

#endif //include guard