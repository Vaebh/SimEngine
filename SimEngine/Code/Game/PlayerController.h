#ifndef PLAYER_CONTROLLER_SIMENGINE
#define PLAYER_CONTROLLER_SIMENGINE

#include "../Structure/Component.h"

class PlayerController : public IComponent
{
public:
	PlayerController();
	//~PlayerController();

	virtual void Update(float in_dt);
};

#endif