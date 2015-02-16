#ifndef RENDERSYSTEM_SIMENGINE
#define RENDERSYSTEM_SIMENGINE

class IRenderableComponent;

#include "../OpenGL/GLIncludes.h"
#include "../Structure/System.h"
#include <vector>

class GameObject;

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

private:
	// TODO - Should change this to a list and change it to support actually removing elements when their GameObjects have been deleted.
	std::vector<IRenderableComponent*> m_components;
};

#endif