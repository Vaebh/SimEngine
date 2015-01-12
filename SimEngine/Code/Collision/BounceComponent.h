#ifndef BOUNCE_COMPONENT_SIMENGINE
#define BOUNCE_COMPONENT_SIMENGINE

#include "../Collision/CollisionComponent.h"
#include "../Foundation/Foundation.h"

// TODO - I could pass in a callback function through the constructor (or not) that is triggered when the onCollision event is called
// Would mean I wouldn't have to use the event system, and could just keep it for more general usage
// It is probably out of it's scope to be able to subscribe to things on a per Component level, well, it wouldn't be, but would marry it to one
// aspect of the engine too much for my liking. I want it to be useful for a lot more than that

class BounceComponent : public CollisionComponent
{
public:
	BounceComponent(float inBounceSpeed);

	void OnCollision(CollisionComponent* inComponent, Vector3 inCollisionVector);

	void Update(float inDT);

	void OnAttached(GameObject* inGameObject);

	void HandleEvent(uint32_t inEventType, GameObject* inTarget);

public:
	Vector3 mInitialPosition;

private:
	float mBounceSpeed;
	bool mMovementEnabled;
};

#endif