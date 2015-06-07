#ifndef APPLICATION_SIMENGINE
#define APPLICATION_SIMENGINE

class Window;
class GameObjectFactory;

class RenderSystem;
class AudioSystem;
class CollisionSystem;
class StateManager;
class InputManager;
class CameraManager;

#include <memory>

class Application
{
public:
	Application();
	~Application();

	static Application* GetApplication();

	void InitialiseSystems();

	void Update();

	inline Window* GetWindow() {return m_window.get();}
	inline const Window* GetWindow() const {return m_window.get();}

	inline GameObjectFactory* GetGameObjectFactory() { return m_gameObjectFactory.get(); }

	inline InputManager* GetInputManager() { return m_inputManager.get(); }

	inline float GetDeltaTime() {return m_dt;}

private:
	static Application* m_application;

	std::unique_ptr<Window> m_window;

	std::unique_ptr<RenderSystem> m_renderSystem;
	std::unique_ptr<StateManager> m_stateManager;
	std::unique_ptr<InputManager> m_inputManager;
	std::unique_ptr<AudioSystem> m_audioSystem;
	std::unique_ptr<CameraManager> m_cameraManager;
	std::unique_ptr<CollisionSystem> m_collisionSystem;

	std::unique_ptr<GameObjectFactory> m_gameObjectFactory;

	double m_dt;
};

#endif