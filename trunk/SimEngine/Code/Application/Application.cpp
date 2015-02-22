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
	double oldDt = 0;

	float fpsTimer = 0;

	GameObject* testModel = m_gameObjectFactory->Create3DGameObject("cube.bin", "bros.png");
	//testModel->SetScale(Vector3(0.0125f, 0.0125f, 0.0125f));
	testModel->SetScale(Vector3(0.5f, 0.5f, 0.5f));


	GameObject* lightModel = m_gameObjectFactory->Create3DGameObject("cube.bin", "bros.png");
	//testModel->SetScale(Vector3(0.0125f, 0.0125f, 0.0125f));
	lightModel->SetScale(Vector3(0.15f, 0.15f, 0.15f));

	GameObject* thorModel = NULL;

	GameObject* thing = NULL;

	while(!GetWindow()->ShouldWindowClose())
	{
		m_dt = glfwGetTime() - oldDt;
		oldDt = glfwGetTime();

		fpsTimer += m_dt;

		if(fpsTimer > 0.5)
		{
			fpsTimer = 0;
			//cout << "FPS: " << 1 / delta << endl;
		}

		if(m_inputManager->IsKeyDown(GLFW_KEY_COMMA))
		{
			if(thing == NULL)
			{
				//delete testModel;
				//testModel = NULL;

				thing = testModel;

				thorModel = m_gameObjectFactory->Create3DGameObject("thor.bin", "bros.png");
				thorModel->MovePosition(Vector3(0.5f, 0.f, 0.f));
				thorModel->SetScale(Vector3(0.0125f, 0.0125f, 0.0125f));
			}
		}

		if(testModel != NULL)
			testModel->Update(m_dt);

		if(thorModel != NULL)
			thorModel->Update(m_dt);

		lightModel->Update(m_dt);
		lightModel->SetPosition(testModel->GetComponent<RenderableMeshComponent>()->m_lightPos);

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