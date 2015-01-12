#include "../Rendering/RenderableComponent.h"
#include "../Rendering/RenderSystem.h"

IRenderableComponent::IRenderableComponent() : 
mVisible(true),
mShader()
{

}

IRenderableComponent::~IRenderableComponent()
{
	RenderSystem::GetSingleton()->RemoveComponent(this);
}

// TODO - Make an application class which I can request access to systems from, having a singleton for each system is not good

void IRenderableComponent::OnAttached(GameObject* inGameObject)
{
	RenderSystem::GetSingleton()->AddComponent(this);
}