#ifndef TEXTURE_MANAGER_SIMEGINE
#define TEXTURE_MANAGER_SIMEGINE

#include "../Foundation/Foundation.h"
#include "../OpenGL/GLIncludes.h"

#include <map>
#include <string>
#include <utility>

class Texture;
class Image;

typedef std::pair<Texture*, uint32_t> TextureUsagePair;
typedef std::map< std::string, TextureUsagePair > TextureMap;
typedef std::map< std::string, Image* > ImageMap;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	Image* RequestImage(const GLchar* in_texName);

	void LoadTextureAtlas(const char* in_atlasName);

	void UnloadTexture(std::string in_texName);

private:
	Texture* LoadTexture(const GLchar* in_texName);
	Texture* LoadTextureFromFile(const GLchar* in_texName);
	uint32_t AdjustUsageCount(std::string in_texKey, int in_adjustment);

private:
	ImageMap m_imageMap;
	TextureMap m_textureCache;
};

#endif
