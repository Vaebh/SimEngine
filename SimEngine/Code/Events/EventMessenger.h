#ifndef EVENT_MESSENGER_SIMENGINE
#define EVENT_MESSENGER_SIMENGINE

class GameObject;

#include "../Events/EventTypes.h"
#include "../Events/EventCallback.h"
#include "../Foundation/Foundation.h"

#include <map>
#include <vector>
#include <utility>

typedef IEventCallback* MessageDelegate;

class EventMessenger
{
	EventMessenger();

public:
	static EventMessenger* GetSingleton();

	// Will have to add another parameter for passing event specific info, an array of string or uint params maybe
	void RecordEvent(const uint32_t in_eventType, GameObject* in_target, const float in_eventNotificationDelay = 0.f);

	void SubscribeToEvent(const uint32_t in_eventType, GameObject* in_target, MessageDelegate in_msgDel);
	void UnsubscribeToEvent(const uint32_t in_eventType, GameObject* in_target, MessageDelegate in_msgDel);

	// TODO - Add delayed events, will likely need an event queue
	//void Update(float in_dt);

private:
	std::vector<MessageDelegate> GetEventDelegates(const uint32_t in_eventType, GameObject* in_target);

private:
	std::map< std::pair<const uint32_t, GameObject*>, std::vector<MessageDelegate> > m_eventMap;

	static EventMessenger* m_eventMessenger;
};

#endif