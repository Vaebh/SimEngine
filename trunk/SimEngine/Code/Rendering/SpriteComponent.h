#ifndef SPRITE_COMPONENT_SIMENGINE
#define SPRITE_COMPONENT_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../OpenGL/GLUtils.h"
#include "../Rendering/RenderableComponent.h"
#include <string>

class SpriteComponent : public IRenderableComponent
{
public:
	SpriteComponent(const std::string inTexture = "sample.png", int inNumFrames = 1);
	~SpriteComponent();
    
    inline Vector4 GetColourTint() const {return mColourTint;}
    inline void SetColourTint(Vector4 inColourTint) {mColourTint = inColourTint;}

    // These really should not be public
	inline GLuint GetVAO() const {return mVao;}
	inline GLuint GetVBO() const {return mVbo;}

protected:
	virtual void Draw();
	virtual void Update(float inDT);

	inline GLuint GetMoveUniform() const {return mMoveUniform;}
	inline GLuint GetUVUniform() const {return mUVUniform;}
	inline GLuint GetFrameUniform() const {return mFrameUniform;}
	inline GLuint GetColourTintUniform() const {return mColourTintUniform;}

private:
	void Initialise();
	glm::mat4 CalculateMatrix();

	void SetShader(const std::string inVertexShaderSrc, const std::string inFragShaderSrc);

private:
	GLuint mVao;
	GLuint mVbo;

	GLuint mMoveUniform;
	GLuint mUVUniform;
	GLuint mFrameUniform;
	GLuint mColourTintUniform;

	float mWidth;
	float mHeight;

	int mNumFrames;
	int mCurrentFrame;

	Vector4 mColourTint;

	TextureData mTextureData;
};

#endif