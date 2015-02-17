#ifndef TEXTURE_SIMENGINE
#define TEXTURE_SIMENGINE

#include "../Foundation/Foundation.h"
#include "../OpenGL/GLIncludes.h"

#include "../Structure/Vectors.h"

#include <string>

class TextureManager;

class Texture
{
public:
	Texture();
	Texture(const std::string& in_name, GLuint* in_texID, GLenum in_target, Vector2 in_dimensions, TextureManager* in_texManager);
	~Texture();

	void Activate(GLenum in_textureUnit);
	void Bind();

	inline const std::string GetName() const {return m_name;}

	inline GLuint* GetTexID() {return m_textureID;}

	inline const Vector2 GetDimensions() const {return m_dimensions;}

	inline const GLenum GetTarget() const {return m_target;}

private:
	std::string m_name;
	GLuint* m_textureID;
	Vector2 m_dimensions;
	GLenum m_target;

	TextureManager* m_texManager;
};

#endif
