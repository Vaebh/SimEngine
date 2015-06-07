#include "../Game/PlayerController.h"

#include "../Application/Application.h"

#include "../Input/InputManager.h"

#include "../Structure/GameObject.h"

PlayerController::PlayerController()
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

	if (Application::GetApplication()->GetInputManager()->IsKeyDown(GLFW_KEY_W))
	{
		GetOwner()->MovePosition(Vector3(0.f, 250.f * Application::GetApplication()->GetDeltaTime(), 0.f));
	}
	if (Application::GetApplication()->GetInputManager()->IsKeyDown(GLFW_KEY_S))
	{
		GetOwner()->MovePosition(Vector3(0.f, -250.f * Application::GetApplication()->GetDeltaTime(), 0.f));
	}
}