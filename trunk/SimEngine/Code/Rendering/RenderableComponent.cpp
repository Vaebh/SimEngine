#include "../Rendering/RenderableComponent.h"

#include "../Rendering/Texture.h"
#include "../Rendering/TextureManager.h"

IRenderableComponent::IRenderableComponent() : 
m_vao(),
m_vertexBuffer(NULL),
m_shader(),
m_texture(NULL),
m_texManager(NULL),
m_visible(true)
{

}

IRenderableComponent::~IRenderableComponent()
{
	m_texManager->UnloadTexture(m_texture->GetName());
}

void IRenderableComponent::SetTextures(const char* in_texName1, const char* in_texName2, const char* in_texName3, const char* in_texName4)
{
	m_texture = m_texManager->LoadTexture(in_texName1);
}