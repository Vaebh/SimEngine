#include "../Application/Application.h"

#include "../Camera/CameraManager.h"

#include "../Collision/CollisionSystem.h"

#include "../Input/InputManager.h"

#include "../Sound/AudioSystem.h"

#include "../Structure/GameObjectFactory.h"
#include "../Structure/StateManager.h"
#include "../Structure/Window.h"

#include "../Rendering/RenderSystem.h"

#include "../Rendering/RenderableMeshComponent.h"

#include "../Debug/Log.h"
#include "../Utils/Clock.h"

#include "../Game/StateBattle.h"


Application* Application::m_application = NULL;

Application::Application() :
m_dt(0)
{
	m_application = this;

	// Start the clock
	Clock::Get();

	InitialiseSystems();
	Update();
}

Application::~Application()
{

}

Application* Application::GetApplication()
{
	return m_application;
}

void Application::InitialiseSystems()
{
	m_window.reset(new Window("Undead Tactics", 1280, 720));

	m_renderSystem.reset(new RenderSystem());
	m_inputManager.reset(new InputManager(const_cast<GLFWwindow*>(m_window->GetGLFWWindow())));
	m_stateManager.reset(new StateManager());

	Camera* defaultCam = new Camera();
	m_cameraManager.reset(new CameraManager(defaultCam));

	m_audioSystem.reset(new AudioSystem());
	m_audioSystem->Initialise();

	m_collisionSystem.reset(new CollisionSystem());

	m_gameObjectFactory.reset(new GameObjectFactory(this, m_renderSystem.get(), m_stateManager.get(), m_inputManager.get(),
		m_audioSystem.get(), m_cameraManager.get(), m_collisionSystem.get()));
}

void Application::Update()
{
	double oldDt = 0;
	float fpsTimer = 0;

	m_stateManager->PushState(new StateBattle());

	while(!GetWindow()->ShouldWindowClose())
	{
		m_dt = glfwGetTime() - oldDt;
		oldDt = glfwGetTime();

		m_inputManager->Update(m_dt);
		m_stateManager->Update(m_dt);
		m_audioSystem->Update(m_dt);
		m_cameraManager->Update(m_dt);
		m_collisionSystem->Update(m_dt);

		m_renderSystem->Update(m_dt);
		m_renderSystem->Draw();

		// Check for new events
		glfwPollEvents();
	}
}