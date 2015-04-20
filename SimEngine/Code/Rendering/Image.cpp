#include "../Rendering/Image.h"
#include "../Rendering/Texture.h"

Image::Image(char* in_imageName, Vector2 in_uvs, Vector2 in_dimensions, Texture* in_texture) :
m_imageName(in_imageName),
m_uvs(in_uvs),
m_dimensions(in_dimensions),
m_texture(in_texture)
{
	SetPercentOfTexture();
}

Image::~Image()
{

}

void Image::SetPercentOfTexture()
{
	m_percentOfTexture.x = GetDimensions().x / m_texture->GetDimensions().x;
	m_percentOfTexture.y = GetDimensions().y / m_texture->GetDimensions().y;
}