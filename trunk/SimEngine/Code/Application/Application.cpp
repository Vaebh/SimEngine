#include "../Application/Application.h"

Application* Application::m_application = NULL;

Application::Application()
{
	InitialiseSystems();

	m_gameObjectFactory = GameObjectFactory(m_renderSystem.get(), m_stateManager.get(), m_inputManager.get(),
		m_audioSystem.get(), m_cameraManager.get(), m_collisionSystem.get());
}

// GOING TO JUST ADD GETTERS TO ALL SYSTEMS IN APPLICATION ITSELF

Application* Application::GetApplication()
{
	return m_application;
}

void Application::InitialiseSystems()
{
	m_renderSystem.reset(new RenderSystem());
	m_stateManager.reset(new StateManager());
	m_inputManager.reset(new InputManager(const_cast<GLFWwindow*>(m_window->GetWindow())));
	m_audioSystem.reset(new AudioSystem());
	m_cameraManager.reset(new CameraManager());
	m_collisionSystem.reset(new CollisionSystem());
}

void Application::Update()
{

}