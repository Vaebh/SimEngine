#ifndef RENDERABLE_MESH_COMPONENT
#define RENDERABLE_MESH_COMPONENT

#include "../Rendering/RenderableComponent.h"

class RenderableMeshComponent : public IRenderableComponent
{
public:
	RenderableMeshComponent(const char* in_textureName, const char* in_meshName);
	~RenderableMeshComponent();

protected:
	virtual void Draw();
	virtual void Update(float in_dt);

	//inline GLuint GetVAO() const {return m_vao;}
	//inline GLuint GetVBO() const {return m_vbo;}

	inline GLuint GetModelUniform() const {return m_modelUniform;}

private:
	void Initialise(const char* in_meshName);
	glm::mat4 CalculateModelMatrix();

	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);
	void SetUniforms();

	bool LoadModel(const char* in_fileName, std::vector<GLfloat>& out_vertexData);

private:
	GLuint m_modelUniform;
	GLuint m_viewUniform;

	Vector3 m_camCenter;
	Vector3 m_camLookat;

	TextureData m_textureData;
};

#endif