#include "../Collision/BounceComponent.h"
#include "../Rendering/RenderSystem.h"
#include "../Events/EventMessenger.h"
#include "../Structure/GameObject.h"
#include <iostream>

namespace
{
	void HandleEventFree(uint32_t inEventType, GameObject* inTarget)
	{
		if(inEventType == COLLISION)
		{
			std::cout << "\nBALL COLLIDED YO FUCK YEAH FREE FUNCTION\n";
		}
	}
}

BounceComponent::BounceComponent(float inBounceSpeed) :
CollisionComponent(),
mBounceSpeed(inBounceSpeed),
mInitialPosition(Vector3()),
mMovementEnabled(false)
{
	
}

void BounceComponent::HandleEvent(uint32_t inEventType, GameObject* inTarget)
{
	if(inEventType == COLLISION)
	{
		std::cout << "\nBALL COLLIDED YO\n" << std::endl;
	}
}

void BounceComponent::OnAttached(GameObject* inGameObject)
{
	CollisionComponent::OnAttached(inGameObject);

	mInitialPosition = inGameObject->GetPosition();

	// Example event usage
	//IEventCallback* newCallback = new EventCallbackMember<BounceComponent>(this, &BounceComponent::HandleEvent);
	//newCallback(BALL_COLLISION);

	//IEventCallback* newCallbackFree = new EventCallbackFree(&HandleEventFree);
	//newCallbackFree(BALL_COLLISION);

	//EventMessenger::GetSingleton()->SubscribeToEvent(BALL_COLLISION, m_owner, newCallback);
	//EventMessenger::GetSingleton()->SubscribeToEvent(COLLISION, m_owner, newCallbackFree);
}

void BounceComponent::OnCollision(CollisionComponent* inComponent, Vector3 inCollisionVector)
{
	CollisionComponent::OnCollision(inComponent, inCollisionVector);

	mMovementEnabled = true;

	Vector3 dirVec(0.f, -1.f, 0.f);

	if(m_owner->GetPosition().x > inComponent->mBoundingBox.right)
	{
		dirVec = X_UNIT_POSITIVE3;
	}
	else if(m_owner->GetPosition().x < inComponent->mBoundingBox.left)
	{
		dirVec = X_UNIT_NEGATIVE3;
	}
	else if(m_owner->GetPosition().y > inComponent->mBoundingBox.top)
	{
		dirVec = Y_UNIT_POSITIVE3;
	}
	else if(m_owner->GetPosition().y < inComponent->mBoundingBox.bottom)
	{
		dirVec = Y_UNIT_NEGATIVE3;
	}

	if(m_owner->GetVelocity() != Vector3())
	{
		// Reflect the balls velocity based on what side of the bounding box it hits
		Vector3 velocityNorm = glm::normalize(m_owner->GetVelocity());
		m_owner->SetVelocity((-2 * (glm::dot(velocityNorm, dirVec)) * dirVec - velocityNorm));
	}

	// Add offset vector so bounces further from the center deflect more
	inCollisionVector *= 4;
	m_owner->MoveVelocity(inCollisionVector);

	m_owner->SetVelocity(glm::normalize(m_owner->GetVelocity()) * mBounceSpeed);
}

void BounceComponent::Update(float in_dt)
{
	CollisionComponent::Update(in_dt);
}