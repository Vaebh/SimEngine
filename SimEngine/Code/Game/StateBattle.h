#ifndef STATE_BATTLE_UT
#define STATE_BATTLE_UT

#include "../Structure/State.h"

class StateBattle : public IState
{
public:
	StateBattle();
	~StateBattle();

	virtual void Update(float in_dt);

private:
	GameObject* m_battleGrid;
};

#endif