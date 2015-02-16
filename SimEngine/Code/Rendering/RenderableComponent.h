#ifndef RENDERABLECOMPONENT_SIMENGINE
#define RENDERABLECOMPONENT_SIMENGINE

class Buffer;

#include "../Rendering/Shader.h"
#include "../Rendering/VertexArray.h"

#include "../Structure/Component.h"

class IRenderableComponent : public IComponent
{
public:
	IRenderableComponent();
	~IRenderableComponent();

	inline const Shader& GetShader() const {return m_shader;}
	inline bool IsVisible() const {return m_visible;}

	virtual void Update(float in_dt) = 0;
	virtual void Draw() = 0;

	virtual void OnAttached(GameObject* in_gameObject);

	virtual glm::mat4 CalculateModelMatrix() = 0;

	inline void SetVisible(bool in_isVisible) {m_visible = in_isVisible;}

	inline const VertexArray& GetVAO() const {return m_vao;}

protected:
	virtual void AddUniforms() = 0;

protected:
	Shader m_shader;

	VertexArray m_vao;
	Buffer* m_vertexBuffer;

	bool m_visible;

	// Should probably just be in one place, maybe a pointer to the camera instead?
	glm::mat4 m_viewMatrix;
};

#endif