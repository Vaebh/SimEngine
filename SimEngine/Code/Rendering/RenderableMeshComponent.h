#ifndef RENDERABLE_MESH_COMPONENT
#define RENDERABLE_MESH_COMPONENT

#include "../Rendering/RenderableComponent.h"

class RenderableMeshComponent : public IRenderableComponent
{
public:
	RenderableMeshComponent(const char* in_meshName, const char* in_textureName);
	~RenderableMeshComponent();

	virtual void OnAttached(GameObject* in_gameObject);
	virtual void OnDetached(GameObject* in_gameObject);

	Vector3 m_lightPos;

protected:
	virtual void Draw();
	virtual void Update(float in_dt);

	void Initialise();
	void SetVertexData();
	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);

	glm::mat4 CalculateModelMatrix();

	void AddUniforms();

private:
	bool LoadModel(const char* in_fileName, std::vector<GLfloat>& out_vertexData);

protected:
	std::string m_meshName;
	std::string m_textureName;
};

#endif