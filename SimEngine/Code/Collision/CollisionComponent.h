#ifndef COLLISION_COMPONENT_SIMENGINE
#define COLLISION_COMPONENT_SIMENGINE

#include "../Structure/Component.h"
#include "../Structure/Rectangle.h"

class CollisionComponent : public IComponent
{
public:
	CollisionComponent();
	~CollisionComponent();
	virtual void Update(float inDT);

	void AddComponent(CollisionComponent* inCollisionComponent);
	void RemoveComponent(CollisionComponent* inCollisionComponent);

	bool IsColliding(Rectangle inBoundingBox, GameObject* inGameObject);

	virtual void OnAttached(GameObject* inGameObject);
	virtual void OnCollision(CollisionComponent* inComponent, Vector3 inCollisionVector);

	bool IsIntersecting(Rectangle inA);

	void PrePositionSet(Vector3 inNewPosition);

public:
	Rectangle mBoundingBox;

protected:
	Rectangle CreateBoundingBox(Vector3 inPosition);
};

#endif