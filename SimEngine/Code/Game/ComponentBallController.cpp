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
	EventMessenger::GetSingleton()->UnsubscribeToEvent(INPUT_SPACE_PRESS, m_owner, mCallbackMember.get());
	EventMessenger::GetSingleton()->UnsubscribeToEvent(DEATH, m_owner, mCallbackMember.get());

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
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_SPACE_PRESS, m_owner, mCallbackMember.get());
	EventMessenger::GetSingleton()->SubscribeToEvent(DEATH, m_owner, mCallbackMember.get());
}

void ComponentBallController::OnDetached(GameObject* inGameObject)
{
	IComponent::OnDetached(inGameObject);

	/*EventMessenger::GetSingleton()->UnsubscribeToEvent(INPUT_SPACE_PRESS, m_owner, mCallbackMember.get());
	EventMessenger::GetSingleton()->UnsubscribeToEvent(DEATH, m_owner, mCallbackMember.get());

	mCallbackMember.reset();*/
}

void ComponentBallController::LaunchBall()
{
	if(!mBallModel->IsMovementEnabled())
	{
		// TODO - Hold this as part of the models construction
		m_owner->SetVelocity(Vector3(0.f, 0.9f, 0.f));

		mBallModel->EnableMovement(true);
		mAiming = false;
	}
}

void ComponentBallController::CheckForWindowCollision()
{
	Vector3 velocity = m_owner->GetVelocity();

	if(m_owner->GetPosition().y >= 0.95f)
	{
		velocity *= m_owner->GetVelocity().y < 0 ? 1 : -1;
	}

	if(m_owner->GetPosition().x >= 0.95f)
	{
		velocity *= m_owner->GetVelocity().x < 0 ? 1 : -1;
	}

	if(m_owner->GetPosition().x <= -0.95f)
	{
		velocity *= m_owner->GetVelocity().x > 0 ? 1 : -1;
	}

	m_owner->SetVelocity(velocity);
}

void ComponentBallController::Update(float in_dt)
{
	CheckForWindowCollision();

	if(mAiming && mAimingObject)
	{
		m_owner->SetPosition(Vector3(mAimingObject->GetPosition().x, mAimingObject->GetPosition().y + mAimingObject->GetScale().y, 0.f));
		m_owner->GetVelocity() = Vector3();
	}

	//if(mBallModel->IsMovementEnabled() && (m_owner->GetPosition().y <= -1.2f || glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_C)))
	{
		m_owner->GetVelocity() = Vector3();
		mBallModel->EnableMovement(false);
		m_owner->SetPosition(mBallModel->GetInitialPosition());

		EventMessenger::GetSingleton()->RecordEvent(DEATH, m_owner);
	}
}