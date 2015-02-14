#include "../Structure/GameObjectFactory.h"

GameObjectFactory::GameObjectFactory() {}

GameObjectFactory::GameObjectFactory(RenderSystem* in_renderSystem, StateManager* in_stateManager, InputManager* in_inputManager,
		AudioSystem* in_audioSystem, CameraManager* in_cameraManager, CollisionSystem* in_collisionSystem) :
m_renderSystem(in_renderSystem),
m_stateManager(in_stateManager),
m_inputManager(in_inputManager),
m_audioSystem(in_audioSystem),
m_cameraManager(in_cameraManager),
m_collisionSystem(in_collisionSystem)
{

}

GameObject* GameObjectFactory::CreateGameObject()
{
	GameObject* newObject = new GameObject();
	newObject->SetCameraManager(m_cameraManager);

	return newObject;
}