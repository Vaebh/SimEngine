#ifndef RENDERABLE_MESH_COMPONENT
#define RENDERABLE_MESH_COMPONENT

#include "../Rendering/RenderableComponent.h"
#include <string>

class RenderableMeshComponent : public IRenderableComponent
{
public:
	RenderableMeshComponent(std::string in_tex);
	~RenderableMeshComponent();

protected:
	virtual void Draw();
	virtual void Update(float in_dt);

	inline GLuint GetVAO() const {return m_vao;}
	inline GLuint GetVBO() const {return m_vbo;}

	inline GLuint GetModelUniform() const {return m_modelUniform;}

private:
	void Initialise();
	glm::mat4 CalculateModelMatrix();

	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);

private:
	GLuint m_vao;
	GLuint m_vbo;

	GLuint m_modelUniform;

	Vector3 m_camCenter;
	Vector3 m_camLookat;

	TextureData m_textureData;
};

#endif