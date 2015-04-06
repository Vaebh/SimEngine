#ifndef SPRITEBATCHER_SIMENGINE
#define SPRITEBATCHER_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Rendering/SpriteComponent.h"

#include <list>

/*
Should a batch be something non Singleton-y, or should it be something that is passed batches of sprites
either every frame or just until they're removed. Maybe batches are things you build and they're all stored by the renderSystem
and then you call the drawBatch function on each one. Maybe DrawBatch accepts a shader? SpriteBatcher should accept a FrameBuffer anyway
*/

// TODO - Add removeSprite method
// TODO - Rework the m_sprites datastructure to be less terrible

class SpriteBatcher
{
public:
	SpriteBatcher();
	~SpriteBatcher();

	void AddSprite(SpriteComponent* in_newSpriteComp);

	void DrawBatch();

private:
	Shader* m_activeShader;
	Texture* m_activeTexture;

	VertexArray* m_activeVAO;
	std::vector< std::pair<std::string, std::list<SpriteComponent*>> > m_sprites;
};

#endif