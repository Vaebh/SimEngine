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

void FragileCollisionComponent::Update(float inDT)
{
	if(mDying)
	{
		mOwner->ScaleBy(Vector3(-0.1f * inDT, -0.1f * inDT, 0.f));
		mBoundingBox = CreateBoundingBox(mOwner->GetPosition());
	}

	if(mOwner->mScale.x <= 0.001f)
	{
		mDead = true;
	}
}