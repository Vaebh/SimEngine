#ifndef SIMENGINE_STATEMANAGER
#define SIMENGINE_STATEMANAGER

#include "../Structure/State.h"

class StateManager
{
public:
	StateManager();
	~StateManager();

	static StateManager* GetSingleton();

	const IState* GetActiveState() const;

	void PushState(IState* const inNewState);
	void PopState();

	void Update(float inDT);

private:
	IState* mActiveState;

	std::vector<IState*> mStateHierarchy;

	static StateManager* mStateManager;
};

#endif