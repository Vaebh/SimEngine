#ifndef RENDERABLE_MESH_COMPONENT
#define RENDERABLE_MESH_COMPONENT

#include "../Rendering/RenderableComponent.h"

class RenderableMeshComponent : public IRenderableComponent
{
public:
	RenderableMeshComponent(const char* in_meshName);
	~RenderableMeshComponent();

	Vector3 m_lightPos;

protected:
	virtual void Draw();
	virtual void Update(float in_dt);

	void AddUniforms();

private:
	void Initialise(const char* in_meshName);
	glm::mat4 CalculateModelMatrix();

	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);

	bool LoadModel(const char* in_fileName, std::vector<GLfloat>& out_vertexData);
};

#endif