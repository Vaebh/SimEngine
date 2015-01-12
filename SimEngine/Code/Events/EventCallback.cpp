#include "../Events/EventCallback.h"
#include <assert.h>

EventCallbackFree::EventCallbackFree(void (*inEventCallbackFunc)(uint32_t, GameObject*)) : 
mEventCallbackFunc(inEventCallbackFunc)
{
	assert(mEventCallbackFunc);
}

void EventCallbackFree::operator() (uint32_t inEventType, GameObject* inTarget)
{
	//std::cout << "\nFree function callback\n";
	mEventCallbackFunc(inEventType, inTarget);
}