#include "../Rendering/RenderableComponent.h"

#include "../Debug/Log.h"

#include "../Rendering/Image.h"
#include "../Rendering/Texture.h"
#include "../Rendering/TextureManager.h"

#include <cstdarg>

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

}

Image* IRenderableComponent::RequestImage(const char* in_imgName)
{
	Image* const newImage = m_texManager->RequestImage(in_imgName);
	if(m_texture == NULL && newImage != NULL)
		m_texture = newImage->GetTexture();

	return newImage;
}

std::vector<Image*> IRenderableComponent::RequestImages(uint32_t in_numArgs, ...)
{
	va_list args;
    va_start(args, in_numArgs);

	std::vector<Image*> requestedImages;

	for(int i = 0; i < in_numArgs; ++i)
	{
		const char* imgName = va_arg(args, const char*);
		Image* const reqImage = m_texManager->RequestImage(imgName);

		if(reqImage != NULL)
			requestedImages.push_back(reqImage);

		Log().Get() << imgName;
	}

	va_end(args);

	return requestedImages;
}

void IRenderableComponent::PreDraw()
{

}