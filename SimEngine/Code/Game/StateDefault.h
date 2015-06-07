#ifndef STATE_DEFAULT_SIMENGINE
#define STATE_DEFAULT_SIMENGINE

#include "../Foundation/Foundation.h"
#include "../Structure/State.h"

#include <memory>

class StateDefault : public IState
{
public:
	StateDefault();
	~StateDefault();

	virtual void Update(float in_dt);

private:
	std::unique_ptr<GameObject> m_player;
};

#endif