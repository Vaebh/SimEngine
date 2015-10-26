#ifndef SPRITEBATCHER_SIMENGINE
#define SPRITEBATCHER_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Rendering/SpriteComponent.h"

class Batch;

class SpriteBatcher
{
public:
	SpriteBatcher();
	~SpriteBatcher();

	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);

	void AddUniforms();

	void AddSprite(SpriteComponent* in_newSpriteComp);

	void DrawBatchs();
	void FlushBatchData();

private:
	std::vector< SpriteComponent* > m_sprites;

	std::vector < Batch* > m_batchs;

	//bool m_batchsDirty;
};

#endif