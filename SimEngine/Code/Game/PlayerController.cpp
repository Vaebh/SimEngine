#include "../Game/PlayerController.h"

#include "../Application/Application.h"

#include "../Game/ProjectileComponent.h"

#include "../Input/InputManager.h"

#include "../Structure/GameObject.h"
#include "../Structure/GameObjectFactory.h"

PlayerController::PlayerController() :
m_bullet(nullptr),
m_fired(false),
m_fireTimer(0.f),
m_fireInterval(0.1f)
{

}

PlayerController::~PlayerController()
{
	for each (GameObject* bullet in m_bullets)
	{
		delete bullet;
	}
}

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

		m_bullets.push_back(Application::GetApplication()->GetGameObjectFactory()->CreateSpriteGameObject("testAnim2"));
		m_bullets.back()->SetPosition(GetOwner()->GetPosition());
		m_bullets.back()->SetScale(Vector3(0.5f, 0.5f, 0.5f));

		Vector3 dir = glm::normalize(Vector3(Application::GetApplication()->GetInputManager()->GetMousePos(), 0.f) - GetOwner()->GetPosition());
		m_bullets.back()->Attach(new ProjectileComponent(250.f, dir));
	}

	for each (GameObject* bullet in m_bullets)
	{
		bullet->Update(in_dt);
	}
}