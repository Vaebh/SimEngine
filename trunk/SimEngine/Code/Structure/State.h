#ifndef STATE_SIMENGINE
#define STATE_SIMENGINE

#include "../Structure/GameObject.h"

class GameObject;

class IState
{
public:
	virtual ~IState() {}
	virtual void Update(float in_dt) = 0;

protected:
	std::vector<GameObject*> mGameObjects;
};

#endif