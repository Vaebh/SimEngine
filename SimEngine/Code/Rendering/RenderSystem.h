#ifndef RENDERSYSTEM_SIMENGINE
#define RENDERSYSTEM_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Structure/System.h"
#include "../Rendering/TextureManager.h"

#include <vector>

class IRenderableComponent;

class RenderSystem : public ISystem
{
public:
	RenderSystem();
	~RenderSystem();

	void AddComponent(IRenderableComponent* inRenderableComponent);
	void RemoveComponent(IRenderableComponent* inRenderableComponent);
	void SetFrameBufferTarget(GLuint inFrameBuffer = 0);

	virtual void Update(float in_dt);

	void Draw();

	inline TextureManager* GetTextureManager() {return &m_texManager;}

private:
	// TODO - Should change this to a list and change it to support actually removing elements when their GameObjects have been deleted.
	std::vector<IRenderableComponent*> m_components;

	TextureManager m_texManager;
};

#endif