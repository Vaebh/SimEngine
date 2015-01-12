#ifndef FRAGILE_COLLISION_COMPONENT_SIMENGINE
#define FRAGILE_COLLISION_COMPONENT_SIMENGINE

#include "../Collision/CollisionComponent.h"

class FragileCollisionComponent : public CollisionComponent
{
public:
	FragileCollisionComponent(int inHealth = 1);

	void OnCollision(CollisionComponent* inComponent, Vector3 inCollisionVector);

	void Update(float inDT);

public:
	bool mDead;

private:
	int mHealth;
	bool mDying;
};

#endif