#include "../Game/ComponentBallController.h"
#include "../Rendering/RenderSystem.h"

ComponentBallController::ComponentBallController(ComponentBallModel* inBallModel) : 
IComponent()
,mBallModel(inBallModel)
,mAiming(true)
,mAimingObject(NULL)
{
	assert(mBallModel);
}

ComponentBallController::~ComponentBallController()
{
	// TODO - Can't unsubscribe in both detach and this and have this not fuck up, should think of better way to do it
	EventMessenger::GetSingleton()->UnsubscribeToEvent(INPUT_SPACE_PRESS, mOwner, mCallbackMember.get());
	EventMessenger::GetSingleton()->UnsubscribeToEvent(DEATH, mOwner, mCallbackMember.get());

	mCallbackMember.reset();
}

void ComponentBallController::HandleEvent(uint32_t inEventType, GameObject* inTarget)
{
	if(inEventType == INPUT_SPACE_PRESS)
	{
		LaunchBall();
	}
	else if(inEventType == DEATH)
	{
		mAiming = true;
	}
}

void ComponentBallController::OnAttached(GameObject* inGameObject)
{
	IComponent::OnAttached(inGameObject);

	mCallbackMember.reset(new EventCallbackMember<ComponentBallController>(this, &ComponentBallController::HandleEvent));
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_SPACE_PRESS, mOwner, mCallbackMember.get());
	EventMessenger::GetSingleton()->SubscribeToEvent(DEATH, mOwner, mCallbackMember.get());
}

void ComponentBallController::OnDetached(GameObject* inGameObject)
{
	IComponent::OnDetached(inGameObject);

	/*EventMessenger::GetSingleton()->UnsubscribeToEvent(INPUT_SPACE_PRESS, mOwner, mCallbackMember.get());
	EventMessenger::GetSingleton()->UnsubscribeToEvent(DEATH, mOwner, mCallbackMember.get());

	mCallbackMember.reset();*/
}

void ComponentBallController::LaunchBall()
{
	if(!mBallModel->IsMovementEnabled())
	{
		// TODO - Hold this as part of the models construction
		mOwner->mVelocity = Vector3(0.f, 0.9f, 0.f);

		mBallModel->EnableMovement(true);
		mAiming = false;
	}
}

void ComponentBallController::CheckForWindowCollision()
{
	if(mOwner->GetPosition().y >= 0.95f)
	{
		mOwner->mVelocity.y *= mOwner->mVelocity.y < 0 ? 1 : -1;
	}

	if(mOwner->GetPosition().x >= 0.95f)
	{
		mOwner->mVelocity.x *= mOwner->mVelocity.x < 0 ? 1 : -1;
	}

	if(mOwner->GetPosition().x <= -0.95f)
	{
		mOwner->mVelocity.x *= mOwner->mVelocity.x > 0 ? 1 : -1;
	}
}

void ComponentBallController::Update(float inDT)
{
	CheckForWindowCollision();

	if(mAiming && mAimingObject)
	{
		mOwner->SetPosition(Vector3(mAimingObject->GetPosition().x, mAimingObject->GetPosition().y + mAimingObject->mScale.y, 0.f));
		mOwner->mVelocity = Vector3();
	}

	if(mBallModel->IsMovementEnabled() && (mOwner->GetPosition().y <= -1.2f || glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_C)))
	{
		mOwner->mVelocity = Vector3();
		mBallModel->EnableMovement(false);
		mOwner->SetPosition(mBallModel->GetInitialPosition());

		EventMessenger::GetSingleton()->RecordEvent(DEATH, mOwner);
	}
}