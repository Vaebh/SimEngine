#ifndef FOLLOWMOUSE_COMPONENT_SIMENGINE
#define FOLLOWMOUSE_COMPONENT_SIMENGINE

#include "../Structure/Component.h"

enum AXIS
{
	X_AXIS,
	Y_AXIS,
	BOTH_AXIS
};

class FollowMouseComponent : public IComponent
{
public:
	FollowMouseComponent(AXIS inAxis);

	void Update(float inDT);

	inline AXIS GetAxis() const {return mAxis;}

private:
	AXIS mAxis;
};

#endif