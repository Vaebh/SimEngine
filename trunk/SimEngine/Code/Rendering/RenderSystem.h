#ifndef RENDERSYSTEM_SIMENGINE
#define RENDERSYSTEM_SIMENGINE

class IRenderableComponent;

#include "../OpenGL/GLIncludes.h"
//#include "../Rendering/RenderableComponent.h"
#include "../Structure/System.h"
#include <vector>

class GameObject;

class RenderSystem : public ISystem
{
public:
	RenderSystem();
	~RenderSystem();

	//const std::string GetSystemID();

	static RenderSystem* GetSingleton();

	void AddComponent(IRenderableComponent* inRenderableComponent);
	void RemoveComponent(IRenderableComponent* inRenderableComponent);
	void SetFrameBufferTarget(GLuint inFrameBuffer = 0);

	virtual void Update(float in_dt);

	void Draw();

public:
	static GLFWwindow* mWindow;

private:
	static RenderSystem* mRenderer;

	std::vector<IRenderableComponent*> m_components;
};

#endif