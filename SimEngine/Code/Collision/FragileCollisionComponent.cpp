#include "../Collision/FragileCollisionComponent.h"

FragileCollisionComponent::FragileCollisionComponent(int inHealth) :
CollisionComponent(),
mHealth(inHealth),
mDying(false),
mDead(false)
{

}

void FragileCollisionComponent::OnCollision(CollisionComponent* inComponent, Vector3 inCollisionVector)
{
	CollisionComponent::OnCollision(inComponent, inCollisionVector);

	if(!mDying)
	{
		mHealth -= 1;

		if(mHealth <= 0 && !mDying && !mDead)
		{
			mDying = true;
		}
	}
}

void FragileCollisionComponent::Update(float in_dt)
{
	if(mDying)
	{
		m_owner->ScaleBy(Vector3(-0.1f * in_dt, -0.1f * in_dt, 0.f));
		mBoundingBox = CreateBoundingBox(m_owner->GetPosition());
	}

	if(m_owner->GetScale().x <= 0.001f)
	{
		mDead = true;
	}
}