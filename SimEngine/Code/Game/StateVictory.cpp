#include "../Foundation/Foundation.h"

#include "../Game/StateVictory.h"

#include "../Rendering/RenderSystem.h"
#include "../Rendering/SpriteComponent.h"

StateVictory::StateVictory()
{
	mVictoryCake.reset(new GameObject());
	mVictoryCake->SetPosition(Vector3(0.f, 0.f, 0.f));

	SpriteComponent* cakeSprite = new SpriteComponent("cake.png");
	mVictoryCake->Attach(cakeSprite);

	mGameObjects.push_back(mVictoryCake.get());
}

StateVictory::~StateVictory()
{

}

void StateVictory::HandleEvent(uint32_t inEventType, GameObject* inTarget)
{

}

void StateVictory::Update(float inDT)
{
	for(std::vector<GameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
	{
		if((*it) == NULL)
		{
			it = mGameObjects.erase(it);
		}
		else
		{
			(*it)->Update(inDT);
		}
	}
}