#ifndef GAME_OBJECT_FACTORY
#define GAME_OBJECT_FACTORY

#include "../Structure/GameObject.h"

#include "../Rendering/RenderSystem.h"
#include "../Structure/StateManager.h"
#include "../Input/InputManager.h"
#include "../Sound/AudioSystem.h"
#include "../Camera/CameraManager.h"
#include "../Collision/CollisionSystem.h"

class GameObjectFactory
{
public:
	GameObjectFactory();
	GameObjectFactory(RenderSystem* in_renderSystem, StateManager* in_stateManager, InputManager* in_inputManager,
		AudioSystem* in_audioSystem, CameraManager* in_cameraManager, CollisionSystem* in_collisionSystem);

	GameObject* CreateGameObject();

	void SetCameraManager(CameraManager* in_cameraManager) {m_cameraManager = in_cameraManager;}

private:
	RenderSystem* m_renderSystem;
	StateManager* m_stateManager;
	InputManager* m_inputManager;
	AudioSystem* m_audioSystem;
	CameraManager* m_cameraManager;
	CollisionSystem* m_collisionSystem;
};

#endif