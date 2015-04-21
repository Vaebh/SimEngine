#include "../Rendering/Texture.h"

#include "../Rendering/TextureManager.h"

Texture::Texture(const std::string& in_name, GLuint* in_texID, GLenum in_target, Vector2 in_dimensions, TextureManager* in_texManager) :
m_name(in_name),
m_textureID(in_texID),
m_target(in_target),
m_dimensions(in_dimensions),
m_texManager(in_texManager)
{
	
}

Texture::~Texture()
{
	glDeleteTextures(1, m_textureID);
}

void Texture::Activate(GLenum in_textureUnit)
{
	glActiveTexture(in_textureUnit);
}

void Texture::Bind()
{
	glBindTexture(m_target, *(m_textureID));
}

void Texture::AdjustUsageCount(bool in_increment)
{
	if (in_increment)
		++m_usageCount;
	else
		--m_usageCount;

	if (m_usageCount <= 0)
		m_texManager->UnloadTexture(this);
}