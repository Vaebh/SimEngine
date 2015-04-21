#ifndef TEXTURE_MANAGER_SIMEGINE
#define TEXTURE_MANAGER_SIMEGINE

#include "../Foundation/Foundation.h"
#include "../OpenGL/GLIncludes.h"

#include <map>
#include <string>
#include <utility>

class Texture;
class Image;

typedef std::map< std::string, Image* > ImageMap;
typedef std::map< std::string, Texture* > TextureMap;

// TODO - Make texturemap use unique pointers, what happens when texturemanager gets trashed before it's happened to unload all the textures

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	Image* RequestImage(const GLchar* in_texName);

	void LoadTextureAtlas(const char* in_atlasName);

	void UnloadTexture(Texture* out_textureToDelete);

private:
	Texture* LoadTexture(const GLchar* in_texName);
	Texture* LoadTextureFromFile(const GLchar* in_texName);

private:
	ImageMap m_imageMap;
	TextureMap m_textureCache;
};

#endif
