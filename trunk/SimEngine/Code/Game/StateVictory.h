#ifndef STATE_VICTORY_SIMENGINE
#define STATE_VICTORY_SIMENGINE

#include "../Events/EventMessenger.h"
#include "../Foundation/Foundation.h"
#include "../Structure/State.h"

class StateVictory : public IState
{
public:
	StateVictory();
	~StateVictory();

	virtual void Update(float inDT);

	void HandleEvent(uint32_t inEventType, GameObject* inTarget);

private:
    std::unique_ptr<IEventCallback> mEventCallbackHandler;

	std::unique_ptr<GameObject> mVictoryCake;
};

#endif