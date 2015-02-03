#ifndef APPLICATION_SIMENGINE
#define APPLICATION_SIMENGINE

#include "../Structure/Window.h"

#include "../Structure/GameObjectFactory.h"

#include "../Rendering/RenderSystem.h"
#include "../Structure/StateManager.h"
#include "../Input/InputManager.h"
#include "../Sound/AudioSystem.h"
#include "../Camera/CameraManager.h"
#include "../Collision/CollisionSystem.h"

class Application
{
public:
	Application();

	void InitialiseSystems();

	void Update();

	const Window* GetWindow();

	static Application* GetApplication();

private:
	std::unique_ptr<Window> m_window;

	GameObjectFactory m_gameObjectFactory;

	std::unique_ptr<RenderSystem> m_renderSystem;
	std::unique_ptr<StateManager> m_stateManager;
	std::unique_ptr<InputManager> m_inputManager;
	std::unique_ptr<AudioSystem> m_audioSystem;
	std::unique_ptr<CameraManager> m_cameraManager;
	std::unique_ptr<CollisionSystem> m_collisionSystem;

	static Application* m_application;
};

#endif