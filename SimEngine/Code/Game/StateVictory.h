#ifndef STATE_VICTORY_SIMENGINE
#define STATE_VICTORY_SIMENGINE

#include "../Events/EventMessenger.h"
#include "../Foundation/Foundation.h"
#include "../Structure/State.h"

#include <memory>

class StateVictory : public IState
{
public:
	StateVictory();
	~StateVictory();

	virtual void Update(float in_dt);

	void HandleEvent(uint32_t inEventType, GameObject* inTarget);

private:
    std::unique_ptr<IEventCallback> mEventCallbackHandler;

	std::unique_ptr<GameObject> mVictoryCake;
};

#endif