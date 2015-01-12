#include "../Foundation/Foundation.h"

#include "../OpenGL/GLUtils.h"

#include "../Rendering/SpriteComponent.h"
#include "../Rendering/RenderSystem.h"

#include <iostream>

const GLfloat vertices[] = 
{	// position					//texcoords
	-0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f,
	0.5f,  0.5f, 0.0f, 1.0f,  1.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f,  1.0f, 1.0f,

	0.5f, -0.5f, 0.0f, 1.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f
};

const unsigned int kNumVertsForSprites = 4;

const std::string DEFAULT_VERT_SHADER = "../SimEngine/Assets/Shaders/2DVertexShaderMove.txt";
const std::string DEFAULT_FRAG_SHADER = "../SimEngine/Assets/Shaders/2DFragShaderPlain.txt";

using namespace std;

SpriteComponent::SpriteComponent(const std::string inTexture, int inNumFrames) :
IRenderableComponent(),
mWidth(0),
mHeight(0),
mNumFrames(inNumFrames),
mCurrentFrame(0),
mColourTintUniform(0),
mColourTint(Vector4(0.f, 0.f, 0.f, 1.f))
{
	Initialise();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);

	mTextureData = LoadImage(inTexture.c_str());
}

SpriteComponent::~SpriteComponent()
{
	// TODO - Make some kind of sprite managery class, maybe SpriteBatch, and have it store and bind the vao and vbo as they're the same for every sprite
	// Also maybe use the same shader program for all sprites
    //glDeleteBuffers(1, &mVbo);
    //glDeleteVertexArrays(1, &mVao);
}

void SpriteComponent::Initialise()
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void SpriteComponent::SetShader(const std::string inVertexShaderSrc, const std::string inFragShaderSrc)
{
	if(inVertexShaderSrc.empty() || inFragShaderSrc.empty())
		return;

	mShader.CreateShaderProgram(inVertexShaderSrc, inFragShaderSrc);

	glUseProgram(mShader.GetProgramID());

	glBindVertexArray(mVao);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);

	GLint posAttrib = glGetAttribLocation(mShader.GetProgramID(), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
                     
	GLint texAttrib = glGetAttribLocation(mShader.GetProgramID(), "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(4*sizeof(float)));

	glUniform1i(glGetUniformLocation(mShader.GetProgramID(), "textureSprite"), 0);

	mMoveUniform = glGetUniformLocation(mShader.GetProgramID(), "move");
	mUVUniform = glGetUniformLocation(mShader.GetProgramID(), "spriteOffset");
	mFrameUniform = glGetUniformLocation(mShader.GetProgramID(), "currentFrame");
	mColourTintUniform = glGetUniformLocation(mShader.GetProgramID(), "uniformColour");
}

glm::mat4 SpriteComponent::CalculateMatrix()
{
	glm::mat4 model;
	model = glm::translate(model, GetOwner()->GetPosition()) * glm::scale(model, GetOwner()->mScale) * glm::rotate(model, GetOwner()->mRotationAngle.x, X_UNIT_POSITIVE) * glm::rotate(model, GetOwner()->mRotationAngle.y, Y_UNIT_POSITIVE) * glm::rotate(model, GetOwner()->mRotationAngle.z, Z_UNIT_POSITIVE);

	return model;
}

void SpriteComponent::Update(float inDT)
{
	//mAnimTimer += inDT;
	//IRenderableComponent::Update(inDT);
}

void SpriteComponent::Draw()
{
    glBindTexture(GL_TEXTURE_2D, *(mTextureData.textureID));

	// Calculate transformation
    glUniformMatrix4fv(mMoveUniform, 1, GL_FALSE, glm::value_ptr(CalculateMatrix()));

    float spriteFrameDivisorU = 1.f / mNumFrames;

	glUniform2f(mUVUniform, spriteFrameDivisorU, 1.f);
	glUniform1i(mFrameUniform, mCurrentFrame);

	glUniform4f(mColourTintUniform, mColourTint.x, mColourTint.y, mColourTint.z, mColourTint.w);
}