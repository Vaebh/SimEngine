#ifndef RENDERABLE_MESH_COMPONENT
#define RENDERABLE_MESH_COMPONENT

#include "../Rendering/RenderableComponent.h"
#include <string>

class RenderableMeshComponent : public IRenderableComponent
{
public:
	RenderableMeshComponent(std::string in_tex, std::vector<GLfloat> in_vertexData, int in_numVertices);
	~RenderableMeshComponent();

protected:
	virtual void Draw();
	virtual void Update(float in_dt);

	//inline GLuint GetVAO() const {return m_vao;}
	//inline GLuint GetVBO() const {return m_vbo;}

	inline GLuint GetModelUniform() const {return m_modelUniform;}

private:
	void Initialise(std::vector<GLfloat> in_vertexData);
	glm::mat4 CalculateModelMatrix();

	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);
	void SetUniforms();

private:
	GLuint m_modelUniform;
	GLuint m_viewUniform;

	Vector3 m_camCenter;
	Vector3 m_camLookat;

	TextureData m_textureData;
};

#endif