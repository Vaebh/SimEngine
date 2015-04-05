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

	virtual void OnAttached(GameObject* in_gameObject);
	virtual void OnDetached(GameObject* in_gameObject);

	virtual void Draw();

	inline Texture* GetTexture() {return m_texture;}
	void SetTexture(std::string in_newTex);

protected:
	virtual void Update(float in_dt);

	inline glm::vec2 GetUVs() {return m_uvs;}
	const Vector2 GetDimensions();

	void Initialise();
	void SetVertexData();
	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);

	void AddUniforms();

	glm::mat4 CalculateModelMatrix();

protected:
	std::string m_textureName;

private:
	glm::vec2 m_uvs;
};

#endif