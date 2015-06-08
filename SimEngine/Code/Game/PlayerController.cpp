#include "../Game/PlayerController.h"

#include "../Application/Application.h"

#include "../Input/InputManager.h"

#include "../Structure/GameObject.h"

#include "../Structure/GameObjectFactory.h"

PlayerController::PlayerController() :
m_bullet(nullptr),
m_fired(false),
m_fireTimer(0.f),
m_fireInterval(0.5f)
{

}

#include "../Debug/Log.h"

void PlayerController::Update(float in_dt)
{
	if (Application::GetApplication()->GetInputManager()->IsKeyDown(GLFW_KEY_A))
	{
		GetOwner()->MovePosition(Vector3(-250.f * Application::GetApplication()->GetDeltaTime(), 0.f, 0.f));
	}
	if (Application::GetApplication()->GetInputManager()->IsKeyDown(GLFW_KEY_D))
	{
		GetOwner()->MovePosition(Vector3(250.f * Application::GetApplication()->GetDeltaTime(), 0.f, 0.f));
	}

	if (Application::GetApplication()->GetInputManager()->IsKeyDown(GLFW_KEY_S))
	{
		GetOwner()->MovePosition(Vector3(0.f, 250.f * Application::GetApplication()->GetDeltaTime(), 0.f));
	}
	if (Application::GetApplication()->GetInputManager()->IsKeyDown(GLFW_KEY_W))
	{
		GetOwner()->MovePosition(Vector3(0.f, -250.f * Application::GetApplication()->GetDeltaTime(), 0.f));
	}

	if (m_fired == true)
	{
		m_fireTimer += in_dt;

		if (m_fireTimer >= m_fireInterval)
		{
			m_fireTimer = 0.f;
			m_fired = false;
		}
	}

	if (!m_fired && Application::GetApplication()->GetInputManager()->IsKeyDown(GLFW_KEY_SPACE))
	{
		m_fired = true;

		if (m_bullet != nullptr)
			delete m_bullet;

		m_bullet = Application::GetApplication()->GetGameObjectFactory()->CreateSpriteGameObject("testAnim2");
		m_bullet->SetPosition(GetOwner()->GetPosition());
		m_bullet->SetScale(Vector3(0.5f, 0.5f, 0.5f));

		m_bulletDir = glm::normalize(Vector3(Application::GetApplication()->GetInputManager()->GetMousePos(), 0.f) - GetOwner()->GetPosition());
	}

	if (m_bullet != nullptr)
	{
		/*Vector3 lerpVec = Vector3(Application::GetApplication()->GetDeltaTime());
		Vector3 lerpedThing = glm::mix(m_bullet->GetPosition(), Vector3(Application::GetApplication()->GetInputManager()->GetMousePos(), 0.f), Application::GetApplication()->GetDeltaTime() * 3.f);
		m_bullet->SetPosition(lerpedThing);*/


		m_bullet->MovePosition(m_bulletDir * 0.1f);
	}
}