#ifndef RENDERABLECOMPONENT_SIMENGINE
#define RENDERABLECOMPONENT_SIMENGINE

#include "../Structure/Component.h"
#include "../Rendering/Shader.h"

class IRenderableComponent : public IComponent
{
public:
	IRenderableComponent();
	~IRenderableComponent();

	inline Shader GetShader() const {return mShader;}
	inline bool IsVisible() const {return mVisible;}

	virtual void Update(float inDT) = 0;
	virtual void Draw() = 0;

	virtual void OnAttached(GameObject* inGameObject);

protected:
	Shader mShader;
	bool mVisible;

	// Should probably just be in one place, maybe a pointer to the camera instead?
	glm::mat4 m_viewMatrix;
};

#endif