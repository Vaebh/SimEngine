#include "../Events/EventMessenger.h"

EventMessenger* EventMessenger::mEventMessenger = NULL;

EventMessenger::EventMessenger() {}

EventMessenger* EventMessenger::GetSingleton()
{
	if(!mEventMessenger)
	{
		mEventMessenger = new EventMessenger();
	}

	return mEventMessenger;
}

std::vector<MessageDelegate> EventMessenger::GetEventDelegates(const uint32_t in_eventType, GameObject* in_target)
{
	std::pair<const uint32_t, GameObject*> keyPair = std::make_pair(in_eventType, in_target);
	return m_eventMap[keyPair];
}

// Fires the delegates for the triggered event
void EventMessenger::RecordEvent(const uint32_t in_eventType, GameObject* in_target, const float in_eventNotificationDelay)
{
	if(in_target == NULL)
		return;

	std::vector<MessageDelegate> delegates = GetEventDelegates(in_eventType, in_target);

	for(int i = 0; i < delegates.size(); ++i)
	{
		(*delegates[i])(in_eventType, in_target);
	}
}

void EventMessenger::SubscribeToEvent(const uint32_t in_eventType, GameObject* in_target, MessageDelegate in_msgDel)
{
	if(in_msgDel == NULL || in_target == NULL)
		return;

	std::pair<const uint32_t, GameObject*> keyPair = std::make_pair(in_eventType, in_target);
	std::vector<MessageDelegate>& delegates = m_eventMap[keyPair];

	for(int i = 0; i < delegates.size(); ++i)
	{
		if(delegates[i] == in_msgDel)
			return;
	}

	delegates.push_back(in_msgDel);
}


void EventMessenger::UnsubscribeToEvent(const uint32_t in_eventType, GameObject* in_target, MessageDelegate in_msgDel)
{
	if(in_msgDel == NULL || in_target == NULL)
		return;

	std::pair<const uint32_t, GameObject*> keyPair = std::make_pair(in_eventType, in_target);
	std::vector<MessageDelegate>& delegates = m_eventMap[keyPair];

	for(int i = 0; i < delegates.size(); ++i)
	{
		if(delegates[i] == in_msgDel)
		{
			delegates.erase(delegates.begin()+i);
			break;
		}
	}

	if(delegates.empty())
		m_eventMap.erase(keyPair);
}