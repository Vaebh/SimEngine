#ifndef RENDERABLE_MESH_COMPONENT
#define RENDERABLE_MESH_COMPONENT

#include "../Foundation/Foundation.h"
#include "../OpenGL/GLUtils.h"
#include "../Rendering/RenderableComponent.h"

class RenderableMeshComponent : public IRenderableComponent
{
public:
	RenderableMeshComponent(const char* in_meshName, const char* in_textureName);
	~RenderableMeshComponent();

protected:
	virtual void Draw();
	virtual void Update(float in_dt);

	void AddUniforms();

	//inline GLuint GetVAO() const {return m_vao;}
	//inline GLuint GetVBO() const {return m_vbo;}

	void HandleEvent(uint32_t in_eventType, GameObject* in_target);

private:
	void Initialise(const char* in_meshName);
	glm::mat4 CalculateModelMatrix();

	void SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc);

	bool LoadModel(const char* in_fileName, std::vector<GLfloat>& out_vertexData);

private:
	Vector3 m_camCenter;
	Vector3 m_camLookat;

	TextureData m_textureData;
};

#endif