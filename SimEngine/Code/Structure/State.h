#ifndef STATE_SIMENGINE
#define STATE_SIMENGINE

#include "../Structure/GameObject.h"

class IState
{
public:
	virtual ~IState() {}
	virtual void Update(float inDT) = 0;

protected:
	std::vector<GameObject*> mGameObjects;
};

#endif