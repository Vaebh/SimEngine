#include "../Application/Application.h"

#include "../Structure/GameObjectFactory.h"

#include "../Rendering/RenderSystem.h"
#include "../Structure/StateManager.h"
#include "../Input/InputManager.h"
#include "../Sound/AudioSystem.h"
#include "../Camera/CameraManager.h"
#include "../Collision/CollisionSystem.h"

#include "../Rendering/RenderableMeshComponent.h"

Application* Application::m_application = NULL;

Application::Application() :
m_dt(0)
{
	m_application = this;

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
	m_window.reset(new Window("SimEngine", 640, 480));

	m_renderSystem.reset(new RenderSystem());
	m_inputManager.reset(new InputManager(const_cast<GLFWwindow*>(m_window->GetGLFWWindow())));
	m_stateManager.reset(new StateManager());

	Camera* defaultCam = new Camera();
	m_cameraManager.reset(new CameraManager(defaultCam));

	m_audioSystem.reset(new AudioSystem());
	m_audioSystem->Initialise();

	m_collisionSystem.reset(new CollisionSystem());

	m_gameObjectFactory.reset(new GameObjectFactory(m_renderSystem.get(), m_stateManager.get(), m_inputManager.get(),
		m_audioSystem.get(), m_cameraManager.get(), m_collisionSystem.get()));
}

void Application::Update()
{
	double olddt = 0;

	float fpsTimer = 0;

	GameObject* const theCube = m_gameObjectFactory->Create3DGameObject("thor.obj", "bros.png");
	theCube->SetScale(Vector3(0.0125f, 0.0125f, 0.0125f));

	while(!GetWindow()->ShouldWindowClose())
	{
		m_dt = glfwGetTime() - olddt;
		olddt = glfwGetTime();

		fpsTimer += m_dt;

		if(fpsTimer > 0.5)
		{
			fpsTimer = 0;
			//cout << "FPS: " << 1 / delta << endl;
		}

		theCube->Update(m_dt);

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