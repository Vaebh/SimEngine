#ifndef TEXTURE_MANAGER_SIMEGINE
#define TEXTURE_MANAGER_SIMEGINE

#include "../Foundation/Foundation.h"
#include "../OpenGL/GLIncludes.h"

#include <map>
#include <string>
#include <utility>

class Texture;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

    Texture* LoadTexture(const GLchar* in_texName);

	void UnloadTexture(std::string in_texName);
	void DumpTextureCache();

private:
	Texture* LoadTextureFromFile(const GLchar* in_texName);
	uint32_t AdjustUsageCount(std::string in_texKey, int in_adjustment);

private:
	//std::vector<Texture*> m_textureCache;
	std::map< std::string, std::pair<Texture*, uint32_t> > m_textureCache;
};

#endif
