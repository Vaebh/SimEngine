#ifndef TEST3D_COMPONENT_SIMENGINE
#define TEST3D_COMPONENT_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../OpenGL/GLUtils.h"
#include "../Rendering/RenderableComponent.h"
#include <string>

class Test3DComponent : public IRenderableComponent
{
public:
	Test3DComponent();
	~Test3DComponent();

    // These really should not be public
	inline GLuint GetVAO() const {return mVao;}
	inline GLuint GetVBO() const {return mVbo;}

protected:
	virtual void Draw();
	virtual void Update(float inDT);

	inline GLuint GetMoveUniform() const {return mMoveUniform;}
	inline GLuint GetUVUniform() const {return mUVUniform;}

private:
	void Initialise();
	glm::mat4 CalculateMatrix();

	void SetShader(const std::string inVertexShaderSrc, const std::string inFragShaderSrc);

private:
	GLuint mVao;
	GLuint mVbo;

	GLuint mMoveUniform;
	GLuint mUVUniform;

	Vector3 m_camCenter;
	Vector3 m_camLookat;

	TextureData mTextureData;
};

#endif