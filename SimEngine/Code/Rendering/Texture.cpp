#include "../Rendering/Texture.h"

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