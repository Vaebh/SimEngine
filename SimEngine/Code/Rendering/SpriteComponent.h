#ifndef SPRITE_COMPONENT_SIMENGINE
#define SPRITE_COMPONENT_SIMENGINE

#include "../Foundation/Foundation.h"
#include "../Rendering/RenderableComponent.h"
#include <string>

// TODO - Sprites should be as big onscreen by default as their actual texture pixel width and depth

class SpriteComponent : public IRenderableComponent
{
public:
	SpriteComponent(const std::string in_texture = "sample.png", const uint32_t in_numFrames = 1);
	~SpriteComponent();

	virtual void OnAttached(GameObject* in_gameObject);
	virtual void OnDetached(GameObject* in_gameObject);

	virtual void Draw();

	inline std::string GetTextureName() {return m_textureName;}

	inline Texture* GetTexture() {return m_texture;}
	void SetTexture(std::string in_newTex);

	inline const float GetAnimSpeed() const {return m_animSpeed;}
	inline void SetAnimSpeed(float in_animSpeed) {m_animSpeed = in_animSpeed;}

	inline const bool IsAnimLooping() const {return m_loopAnim;}
	inline void SetLooping(bool in_looping) {m_loopAnim = in_looping;}

protected:
	virtual void Update(float in_dt);

	Vector2 GetFrameInfo();
	const Vector2 GetDimensions();

	void Initialise();
	void SetVertexData();
	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);

	void AddUniforms();

	glm::mat4 CalculateModelMatrix();

protected:
	std::string m_textureName;

	uint32_t m_numFrames;
	uint32_t m_currentFrame;
	uint32_t m_frameWidth;

	// The animation speed in seconds;
	float m_animSpeed;
	bool m_loopAnim;

	Vector2 m_uvs;

private:
	bool m_initialised;
};

#endif