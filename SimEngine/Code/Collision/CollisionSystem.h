#ifndef COLLISION_SYSTEM_SIMENGINE
#define COLLISION_SYSTEM_SIMENGINE

class CollisionComponent;

#include "../Structure/System.h"
#include "../Structure/Rectangle.h"

class CollisionSystem : public ISystem
{
public:
	// TODO - TURN THESE INTO TEMPLATE METHODS
	void AddComponent(CollisionComponent* inCollisionComponent);
	void RemoveComponent(CollisionComponent* inCollisionComponent);

	void Update(float in_dt);

	bool IsColliding(Rectangle inBoundingBox, CollisionComponent* inCollisionComponent);

	static CollisionSystem* GetSingleton();

private:
	//std::vector<CollisionComponent*> m_components;

	static CollisionSystem* mColSystem;
};

#endif