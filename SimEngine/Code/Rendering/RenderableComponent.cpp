#include "../Rendering/RenderableComponent.h"
#include "../Rendering/RenderSystem.h"

IRenderableComponent::IRenderableComponent() : 
m_visible(true),
m_shader(),
m_vertexBuffer(NULL)
{

}

IRenderableComponent::~IRenderableComponent()
{
	
}

void IRenderableComponent::OnAttached(GameObject* in_gameObject)
{
	
}