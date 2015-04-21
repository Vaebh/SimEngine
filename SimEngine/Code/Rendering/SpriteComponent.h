#ifndef SPRITE_COMPONENT_SIMENGINE
#define SPRITE_COMPONENT_SIMENGINE

class Image;

#include "../Foundation/Foundation.h"

#include "../Rendering/AnimationClip.h"
#include "../Rendering/RenderableComponent.h"

#include <map>
#include <string>

class SpriteComponent : public IRenderableComponent
{
public:
	SpriteComponent(const std::string in_texture = "bros.png", const uint32_t in_numFrames = 1);
	~SpriteComponent();

	virtual void OnAttached(GameObject* in_gameObject);
	virtual void OnDetached(GameObject* in_gameObject);

	virtual void Draw();

	inline Texture* GetTexture() { return m_texture; }

	inline const std::string GetImageName() const {return m_imageName;}
	const std::string GetTextureName();

	void AddAnimation(char* in_animName, uint32_t in_numFrames, char* in_startImage);
	void AddAnimation(char* in_animName, uint32_t in_numFrames, ...);

	bool SetActiveAnimation(const char* in_animName);

	// temp for testing
	AnimationClip* m_activeAnimation;

protected:
	virtual void Update(float in_dt);

	glm::vec4 GetFrameInfo();

	void Initialise();
	void SetVertexData();
	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);

	void AddUniforms();

	glm::mat4 CalculateModelMatrix();

	void SetImageScale();

private:
	// Sets the images up for either normal rendering or animation
	bool SetImages();

protected:
	Image* m_activeImage;
	std::string m_imageName;

	uint32_t m_numFrames;
	uint32_t m_currentFrame;

	std::vector<Image*> m_imageFrames;

	// The animation speed in seconds;
	float m_animSpeed;
	bool m_loopAnim;

	Vector2 m_uvs;

private:
	bool m_initialised;
	Vector3 m_imageScale;

	std::map <std::string, std::unique_ptr< AnimationClip> > m_animationClips;
};

#endif