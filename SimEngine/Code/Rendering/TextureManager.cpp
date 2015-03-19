#include "../Rendering/Texture.h"
#include "../Rendering/TextureManager.h"

#include <iostream>

TextureManager::TextureManager()
{
    int g = 0;
	g++;
}

TextureManager::~TextureManager()
{
    DumpTextureCache();
}

Texture* TextureManager::LoadTexture(const GLchar* in_texName)
{
	std::string str = in_texName;

	AdjustUsageCount(str, 1);

	std::pair<Texture*, uint32_t>& texPair = m_textureCache[str];
	Texture* tex = texPair.first;
	if(tex != NULL)
	{
		return tex;
	}
	
	// If this is a new image
	return LoadTextureFromFile(in_texName);
}

Texture* TextureManager::LoadTextureFromFile(const GLchar* in_texName)
{
	GLuint* texture = new GLuint;
	glGenTextures(1, texture);
	GLint width = 0, height = 0;
    
	unsigned char* image = NULL;
    
	const std::string imagePath = "../SimEngine/Assets/Images/";
    
	std::string amendedPath(in_texName);
	amendedPath = imagePath + amendedPath;
    
	glBindTexture(GL_TEXTURE_2D, *texture);
	image = SOIL_load_image(amendedPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	if(image == NULL)
	{
        std::cout << "Image " << in_texName << " is null!" << std::endl;
		std::cout << "SOIL error: " << SOIL_last_result() << std::endl;
	}
	SOIL_free_image_data(image);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	Texture* newTexture = new Texture(in_texName, texture, GL_TEXTURE_2D, Vector2(width, height), this);
	
	m_textureCache[in_texName] = std::make_pair<Texture*, uint32_t>(newTexture, 0);
    
	return newTexture;
}

void TextureManager::UnloadTexture(std::string in_texName)
{
	Texture* tex = m_textureCache[in_texName].first;
	if(tex != NULL)
	{
		uint32_t curUsageCount = AdjustUsageCount(in_texName, -1);

		if(curUsageCount == 0)
			delete tex;
	}
}

void TextureManager::DumpTextureCache()
{
	m_textureCache.clear();
}

uint32_t TextureManager::AdjustUsageCount(std::string in_texKey, int in_adjustment)
{
	// Increment the usage count
	std::pair<Texture*, uint32_t>& texPair = m_textureCache[in_texKey];
	texPair.second += in_adjustment;

	return texPair.second;
}