#include "../Collision/CollisionComponent.h"
#include "../Collision/CollisionSystem.h"
#include "../Events/EventMessenger.h"
#include "../Structure/GameObject.h"

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
		inNewPosition = m_owner->GetPosition();
	}
	else
	{
		mBoundingBox = newBoundingBox;
	}
}

void CollisionComponent::OnAttached(GameObject* inGameObject)
{
	IComponent::OnAttached(inGameObject);

	mBoundingBox = CreateBoundingBox(inGameObject->GetPosition());

	CollisionSystem::GetSingleton()->AddComponent(this);
}

Rectangle CollisionComponent::CreateBoundingBox(Vector3 inPosition)
{
	Rectangle newBoundingBox;

	newBoundingBox.left = inPosition.x - m_owner->GetScale().x / 2;
	newBoundingBox.right = inPosition.x + m_owner->GetScale().x / 2;

	newBoundingBox.top = inPosition.y + m_owner->GetScale().y / 2;
	newBoundingBox.bottom = inPosition.y - m_owner->GetScale().y / 2;

	return newBoundingBox;
}

void CollisionComponent::OnCollision(CollisionComponent* inComponent, Vector3 inCollisionVector)
{
	EventMessenger::GetSingleton()->RecordEvent(COLLISION, m_owner);
}

void CollisionComponent::Update(float in_dt)
{

}