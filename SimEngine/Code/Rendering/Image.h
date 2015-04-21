#ifndef IMAGE_SIMENGINE
#define IMAGE_SIMENGINE

#include "../Structure/Vectors.h"

#include <string>

class Texture;

//Intermediary between texture and sprite
class Image
{
public:
	Image(std::string in_imageName, Vector2 in_uvs, Vector2 in_dimensions, Texture* in_texture);
	~Image();

	inline const Vector2 GetUVs() {return m_uvs;}

	std::string GetName() const { return m_imageName; }

	inline const Vector2 GetDimensions() {return m_dimensions;}
	inline void SetDimensions(Vector2 in_dimensions) {m_dimensions = in_dimensions;}

	inline const Vector2 GetPercentOfTexture() { return m_percentOfTexture; }
	void SetPercentOfTexture();

	inline Texture* GetTexture() {return m_texture;}

private:
	std::string m_imageName;

	Vector2 m_uvs;
	Vector2 m_dimensions;
	Vector2 m_percentOfTexture;

	Texture* m_texture;
};

#endif