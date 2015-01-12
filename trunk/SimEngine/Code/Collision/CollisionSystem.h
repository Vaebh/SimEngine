#ifndef COLLISION_SYSTEM_SIMENGINE
#define COLLISION_SYSTEM_SIMENGINE

#include "../Structure/System.h"
#include "../Collision/CollisionComponent.h"

class CollisionSystem : public ISystem
{
public:
	// TODO - TURN THESE INTO TEMPLATE METHODS
	void AddComponent(CollisionComponent* inCollisionComponent);
	void RemoveComponent(CollisionComponent* inCollisionComponent);

	void Update(float inDT);

	bool IsColliding(Rectangle inBoundingBox, CollisionComponent* inCollisionComponent);

	static CollisionSystem* GetSingleton();

private:
	std::vector<CollisionComponent*> mComponents;

	static CollisionSystem* mColSystem;
};

#endif