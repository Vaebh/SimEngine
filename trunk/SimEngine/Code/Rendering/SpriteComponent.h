#ifndef SPRITE_COMPONENT_SIMENGINE
#define SPRITE_COMPONENT_SIMENGINE

#include "../Rendering/RenderableComponent.h"
#include <string>

// TODO - Sprites should be as big onscreen by default as their actual texture pixel width and depth

class SpriteComponent : public IRenderableComponent
{
public:
	SpriteComponent(const std::string in_texture = "sample.png");
	~SpriteComponent();

	virtual void Draw();

	inline Texture* GetTexture() {return m_texture;}

protected:
	virtual void Update(float in_dt);

	void AddUniforms();

	inline glm::vec2 GetUVs() {return m_uvs;}

private:
	void Initialise();
	glm::mat4 CalculateModelMatrix();

	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);

protected:
	float m_width;
	float m_height;

private:
	glm::vec2 m_uvs;
};

#endif