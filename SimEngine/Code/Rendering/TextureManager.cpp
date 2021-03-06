#include "../Rendering/TextureManager.h"

#include "../Debug/Log.h"
#include "../Rendering/Image.h"
#include "../Rendering/Texture.h"

#include "../Foundation/StringUtils.h"

#include "tinyxml2.h"

namespace
{
	const std::string IMAGE_PATH = "../SimEngine/Assets/Images/";
	const std::string ATLAS_PATH = IMAGE_PATH + "TextureAtlases/";
}

TextureManager::TextureManager()
{
	LoadTextureAtlas("texAtlas1.xml");
}

TextureManager::~TextureManager()
{
	// TODO - convert from raw loop
	TextureMap::iterator iter;
	for (iter = m_textureCache.begin(); iter != m_textureCache.end(); ++iter)
		delete (*iter).second;

    m_textureCache.clear();
}

// Calls to load texture atlases have to be done manually
void TextureManager::LoadTextureAtlas(const char* in_atlasName)
{
	// TODO - Change so it supports more than pngs
	std::string texturePath = ParseText(in_atlasName, ".")[0] + ".png";
	Texture* const newTexture = LoadTexture(texturePath.c_str());

	tinyxml2::XMLDocument atlasDoc;
	std::string path = ATLAS_PATH + in_atlasName;
	bool docBad = atlasDoc.LoadFile( path.c_str() );

	if (!docBad)
	{
		tinyxml2::XMLElement* textureAtlasElement = atlasDoc.FirstChildElement("TextureAtlas");
		tinyxml2::XMLNode* spriteElement = textureAtlasElement->FirstChild();

		while(spriteElement != NULL)
		{
			std::string spriteName = spriteElement->ToElement()->Attribute("n");
			spriteName = ParseText(spriteName, ".")[0];
			int uvX = 0;
			spriteElement->ToElement()->QueryIntAttribute("x", &uvX);
			int uvY = 0;
			spriteElement->ToElement()->QueryIntAttribute("y", &uvY);
			int width = 0;
			spriteElement->ToElement()->QueryIntAttribute("w", &width);
			int height = 0;
			spriteElement->ToElement()->QueryIntAttribute("h", &height);

			float uvthex = uvX / newTexture->GetDimensions().x;
			float uvthey = uvY / newTexture->GetDimensions().y;

			Image* const newImage = new Image(spriteName, Vector2(uvthex, uvthey), Vector2(width, height), newTexture);
			m_imageMap[spriteName] = newImage;

			spriteElement = spriteElement->NextSibling();
		}
	}
}

Image* TextureManager::RequestImage(const GLchar* in_texName)
{
	Image* const theImage = m_imageMap[in_texName];

	if(theImage != NULL)
	{
		theImage->GetTexture()->AdjustUsageCount(true);

		return theImage;
	}
	else
	{
		// TODO - Add call to loadtexture in the case of no image being found
		Log().Get() << "Image " << in_texName << " not found, relevant atlas may not be loaded";
	}
}

Texture* TextureManager::LoadTexture(const GLchar* in_texName)
{
	Texture* tex = m_textureCache[in_texName];

	if(tex != NULL)
	{
		tex->AdjustUsageCount(true);
		return tex;
	}
	
	// If this is a new texture
	tex = LoadTextureFromFile(in_texName);

	if(tex != NULL)
		tex->AdjustUsageCount(true);

	return tex;
}

Texture* TextureManager::LoadTextureFromFile(const GLchar* in_texName)
{
	GLuint* texture = new GLuint;
	glGenTextures(1, texture);
	GLint width = 0, height = 0;

	unsigned char* image = NULL;

	std::string amendedPath(in_texName);
	amendedPath = IMAGE_PATH + amendedPath;

	glBindTexture(GL_TEXTURE_2D, *texture);
	image = SOIL_load_image(amendedPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(image == NULL)
	{
		Log().Get() << "Image " << in_texName << " is null!";
		Log().Get() << "SOIL error: " << SOIL_last_result();

		return NULL;
	}

	Texture* newTexture = new Texture(in_texName, texture, GL_TEXTURE_2D, Vector2(width, height), this);
	
	m_textureCache[in_texName] = newTexture;

	return newTexture;
}

void TextureManager::UnloadTexture(Texture* out_textureToDelete)
{
	if (out_textureToDelete != NULL)
	{
		m_textureCache.erase(out_textureToDelete->GetName());
		delete out_textureToDelete;
		out_textureToDelete = NULL;
	}
}