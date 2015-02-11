#include "../Rendering/RenderableComponent.h"
#include "../Rendering/RenderSystem.h"

IRenderableComponent::IRenderableComponent() : 
m_visible(true),
m_shader(),
m_numVertices(0)
{

}

IRenderableComponent::~IRenderableComponent()
{
	RenderSystem::GetSingleton()->RemoveComponent(this);
}

// TODO - Make an application class which I can request access to systems from, having a singleton for each system is not good

void IRenderableComponent::OnAttached(GameObject* in_gameObject)
{
	RenderSystem::GetSingleton()->AddComponent(this);
}