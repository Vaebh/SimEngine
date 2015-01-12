#include "../Collision/CollisionComponent.h"
#include "../Collision/CollisionSystem.h"
#include "../Events/EventMessenger.h"

CollisionComponent::CollisionComponent()
{

}

CollisionComponent::~CollisionComponent()
{
	CollisionSystem::GetSingleton()->RemoveComponent(this);
}

bool CollisionComponent::IsIntersecting(Rectangle inA)
{
	Rectangle RectB = mBoundingBox;

	if(inA.right > RectB.left && inA.left < RectB.right &&
		inA.bottom < RectB.top && inA.top > RectB.bottom)
	{
		return true;
	}

	return false;
}

void CollisionComponent::PrePositionSet(Vector3 inNewPosition)
{
	Rectangle newBoundingBox = CreateBoundingBox(inNewPosition);

	if(CollisionSystem::GetSingleton()->IsColliding(newBoundingBox, this))
	{
		inNewPosition = mOwner->GetPosition();
	}
	else
	{
		mBoundingBox = newBoundingBox;
	}
}

void CollisionComponent::OnAttached(GameObject* inGameObject)
{
	mBoundingBox = CreateBoundingBox(inGameObject->GetPosition());

	CollisionSystem::GetSingleton()->AddComponent(this);
}

Rectangle CollisionComponent::CreateBoundingBox(Vector3 inPosition)
{
	Rectangle newBoundingBox;

	newBoundingBox.left = inPosition.x - mOwner->mScale.x / 2;
	newBoundingBox.right = inPosition.x + mOwner->mScale.x / 2;

	newBoundingBox.top = inPosition.y + mOwner->mScale.y / 2;
	newBoundingBox.bottom = inPosition.y - mOwner->mScale.y / 2;

	return newBoundingBox;
}

void CollisionComponent::OnCollision(CollisionComponent* inComponent, Vector3 inCollisionVector)
{
	EventMessenger::GetSingleton()->RecordEvent(COLLISION, mOwner);
}

void CollisionComponent::Update(float inDT)
{

}