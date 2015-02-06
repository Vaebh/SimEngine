#include "../Collision/CollisionSystem.h"
#include "../Foundation/Foundation.h"

// TODO - DECIDE WHERE COLLISION IS HAPPENING AND HOW TO USE IT TO PREVENT MOVEMENT
// TODO - ADD POSITION MANIPULATION METHODS TO GAMEOBJECT AND HAVE THEM CHECK COLLISION FIRST

CollisionSystem* CollisionSystem::mColSystem = NULL;

CollisionSystem* CollisionSystem::GetSingleton()
{
	if(mColSystem == NULL)
	{
		mColSystem = new CollisionSystem();
	}

	return mColSystem;
}

// These two methods should be abstract in System.h
void CollisionSystem::AddComponent(CollisionComponent* inCollisionComponent)
{
	if(inCollisionComponent)
	{
		m_components.push_back(inCollisionComponent);
	}
}

void CollisionSystem::RemoveComponent(CollisionComponent* inCollisionComponent)
{
	if(inCollisionComponent)
	{
		std::vector<CollisionComponent*>::const_iterator it;

		for(it = m_components.begin(); it != m_components.end(); ++it)
		{
			if((*it) == inCollisionComponent)
			{
				m_components.erase(it);

				// Downsize the vector
				std::vector<CollisionComponent*>(m_components).swap(m_components);
				break;
			}
		}
	}
}

bool CollisionSystem::IsColliding(Rectangle inBoundingBox, CollisionComponent* inCollisionComponent)
{
    for(uint32_t i = 0; i < m_components.size(); ++i)
	{
		if(m_components[i] != inCollisionComponent && m_components[i]->IsIntersecting(inBoundingBox))
		{
			Vector3 GameObject1Center = Vector3(inCollisionComponent->mOwner->GetPosition().x + inCollisionComponent->mOwner->m_scale.x / 2, inCollisionComponent->mOwner->GetPosition().y + inCollisionComponent->mOwner->m_scale.y / 2, 0.f);
			Vector3 GameObject2Center = Vector3(m_components[i]->mOwner->GetPosition().x + m_components[i]->mOwner->m_scale.x / 2, m_components[i]->mOwner->GetPosition().y + m_components[i]->mOwner->m_scale.y / 2, 0.f);

			Vector3 collisionVector = inCollisionComponent->mOwner->GetPosition() - m_components[i]->mOwner->GetPosition();

			m_components[i]->OnCollision(inCollisionComponent, collisionVector);
			inCollisionComponent->OnCollision(m_components[i], collisionVector);
			return true;
		}
	}

	return false;
}

void CollisionSystem::Update(float in_dt)
{
	/*for(std::vector<CollisionComponent*>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		if(*it)
		{
			(*it)->Update(in_dt);
		}
	}*/
}