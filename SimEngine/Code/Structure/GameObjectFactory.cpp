#include "../Structure/GameObjectFactory.h"
#include "../Rendering/RenderableMeshComponent.h"
#include "../Rendering/SpriteComponent.h"

GameObjectFactory::GameObjectFactory() {}

GameObjectFactory::GameObjectFactory(Application* in_application, RenderSystem* in_renderSystem, StateManager* in_stateManager, InputManager* in_inputManager,
		AudioSystem* in_audioSystem, CameraManager* in_cameraManager, CollisionSystem* in_collisionSystem) :
m_application(in_application),
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

	newObject->SetApplication(m_application);

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

	return newObject;
}

GameObject* GameObjectFactory::CreateSpriteGameObject(char* in_textureName)
{
	GameObject* newObject = CreateGameObject();
	SpriteComponent* spriteComp = new SpriteComponent(in_textureName);

	newObject->Attach(spriteComp);

	return newObject;
}