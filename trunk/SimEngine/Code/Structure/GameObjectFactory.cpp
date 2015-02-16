#include "../Structure/GameObjectFactory.h"
#include "../Rendering/RenderSystem.h"
#include "../Rendering/RenderableMeshComponent.h"

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

	newObject->SetRenderSystem(m_renderSystem);
	newObject->SetStateManager(m_stateManager);
	newObject->SetInputManager(m_inputManager);
	newObject->SetAudioSystem(m_audioSystem);
	newObject->SetCameraManager(m_cameraManager);
	newObject->SetCollisionSystem(m_collisionSystem);

	return newObject;
}

GameObject* GameObjectFactory::Create3DGameObject(char* in_meshName, char* in_textureName)
{
	GameObject* newObject = CreateGameObject();
	RenderableMeshComponent* rendMeshComp = new RenderableMeshComponent(in_meshName, in_textureName);

	newObject->Attach(rendMeshComp);
	m_renderSystem->AddComponent(rendMeshComp);

	return newObject;
}