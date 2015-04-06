#ifndef RENDERSYSTEM_SIMENGINE
#define RENDERSYSTEM_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Structure/System.h"
#include "../Rendering/TextureManager.h"
#include "../Rendering/SpriteBatcher.h"

#include <vector>

class IRenderableComponent;
class SpriteComponent;

class RenderSystem : public ISystem
{
public:
	RenderSystem();
	~RenderSystem();

	void SetFrameBufferTarget(GLuint inFrameBuffer = 0);

	virtual void Update(float in_dt);

	void Draw();

	inline TextureManager* GetTextureManager() {return &m_texManager;}

	void AddSpriteToBatch(SpriteComponent* in_sprite);

private:
	TextureManager m_texManager;
	SpriteBatcher m_spriteBatcher;
};

#endif