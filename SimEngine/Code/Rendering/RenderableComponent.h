#ifndef RENDERABLECOMPONENT_SIMENGINE
#define RENDERABLECOMPONENT_SIMENGINE

#include "../Structure/Component.h"
#include "../Rendering/Shader.h"

class IRenderableComponent : public IComponent
{
public:
	IRenderableComponent();
	~IRenderableComponent();

	inline Shader GetShader() const {return m_shader;}
	inline bool IsVisible() const {return m_visible;}

	virtual void Update(float in_dt) = 0;
	virtual void Draw() = 0;

	virtual void OnAttached(GameObject* in_gameObject);

	virtual glm::mat4 CalculateModelMatrix() = 0;

	int m_numVertices;

protected:
	Shader m_shader;
	bool m_visible;

	// Should probably just be in one place, maybe a pointer to the camera instead?
	glm::mat4 m_viewMatrix;
};

#endif