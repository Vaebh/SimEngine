#include "../Foundation/Foundation.h"

#include "../Game/BreakoutFactory.h"
#include "../Game/ComponentBallController.h"
#include "../Game/StateLevelOne.h"

#include "../Rendering/RenderSystem.h"
#include "../Rendering/SpriteComponent.h"

#include "../Structure/StateManager.h"
#include "../Game/StateVictory.h"

// TODO - CONVERT THIS OVER ONCE NEW STUFF IS DONE

StateLevelOne::StateLevelOne()
{
	mBall.reset(CreateBall());
	mGameObjects.push_back(mBall.get());

	mPaddle.reset(CreatePaddle());
	mGameObjects.push_back(mPaddle.get());

	ComponentBallController* ballController = mBall->GetComponent<ComponentBallController>();
	if(ballController)
	{
		ballController->SetAimingObject(mPaddle.get());
	}

	/*IEventCallback* newCallbackMember = new EventCallbackMember<StateLevelOne>(this, &StateLevelOne::HandleEvent);
	EventMessenger::GetSingleton()->SubscribeToEvent(COLLISION, mBall.get(), newCallbackMember);*/
	mEventCallbackHandler.reset(new EventCallbackMember<StateLevelOne>(this, &StateLevelOne::HandleEvent));
	EventMessenger::GetSingleton()->SubscribeToEvent(COLLISION, mPaddle.get(), mEventCallbackHandler.get());
	EventMessenger::GetSingleton()->SubscribeToEvent(COLLISION, mBall.get(), mEventCallbackHandler.get());
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_SPACE_PRESS, mBall.get(), mEventCallbackHandler.get());
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_SPACE_RELEASE, mBall.get(), mEventCallbackHandler.get());	mBlockManager.reset(new BlockManager(mGameObjects, ""));
}

StateLevelOne::~StateLevelOne()
{
    EventMessenger::GetSingleton()->UnsubscribeToEvent(COLLISION, mPaddle.get(), mEventCallbackHandler.get());
	EventMessenger::GetSingleton()->UnsubscribeToEvent(COLLISION, mBall.get(), mEventCallbackHandler.get());
    
	EventMessenger::GetSingleton()->UnsubscribeToEvent(INPUT_SPACE_PRESS, mBall.get(), mEventCallbackHandler.get());
	EventMessenger::GetSingleton()->UnsubscribeToEvent(INPUT_SPACE_RELEASE, mBall.get(), mEventCallbackHandler.get());
}

void StateLevelOne::HandleEvent(uint32_t inEventType, GameObject* inTarget)
{
	if(inEventType == COLLISION && inTarget == mPaddle.get())
	{
		//std::cout << "=============PADDLE COLLIDED=============\n";
	}
	else if(inEventType == COLLISION && inTarget == mBall.get())
	{
		//std::cout << "=============BALL COLLIDED=============\n";

		mBall->GetComponent<SpriteComponent>()->SetColourTint(Vector4(0.f, 0.f, 1.f, 0.f));
	}
}

void StateLevelOne::Update(float inDT)
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

	if(mBlockManager)
	{
		mBlockManager->Update(inDT);

		if(mBlockManager->AreAllBlocksDead())
		{
			StateManager::GetSingleton()->PopState();
			StateManager::GetSingleton()->PushState(new StateVictory());
		}
	}
}