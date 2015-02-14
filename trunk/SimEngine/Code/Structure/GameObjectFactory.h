#ifndef GAME_OBJECT_FACTORY
#define GAME_OBJECT_FACTORY

#include "../Structure/GameObject.h"

class GameObjectFactory
{
public:
	GameObjectFactory();
	GameObjectFactory(RenderSystem* in_renderSystem, StateManager* in_stateManager, InputManager* in_inputManager,
		AudioSystem* in_audioSystem, CameraManager* in_cameraManager, CollisionSystem* in_collisionSystem);

	GameObject* CreateGameObject();

private:
	RenderSystem* m_renderSystem;
	StateManager* m_stateManager;
	InputManager* m_inputManager;
	AudioSystem* m_audioSystem;
	CameraManager* m_cameraManager;
	CollisionSystem* m_collisionSystem;
};

#endif