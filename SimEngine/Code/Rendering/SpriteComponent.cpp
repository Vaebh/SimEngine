#include "../Application/Application.h"

#include "../Foundation/Foundation.h"

#include "../OpenGL/GLUtils.h"

#include "../Rendering/SpriteComponent.h"
#include "../Rendering/RenderSystem.h"
#include "../Rendering/Texture.h"

#include "../Structure/GameObject.h"
#include "../Structure/Window.h"

const std::string DEFAULT_VERT_SHADER = "../SimEngine/Assets/Shaders/2DVertexShaderDefault.txt";
const std::string DEFAULT_FRAG_SHADER = "../SimEngine/Assets/Shaders/2DFragShaderDefault.txt";

SpriteComponent::SpriteComponent(const std::string in_texture, const uint32_t in_numFrames) :
IRenderableComponent(),
m_textureName(in_texture),
m_numFrames(in_numFrames),
m_currentFrame(0),
m_frameWidth(0),
m_animSpeed(0.1f),
m_loopAnim(true),
m_uvs(Vector2(0)),
m_initialised(false)
{

}

SpriteComponent::~SpriteComponent()
{
	m_vao.Destroy();
}

void SpriteComponent::Initialise()
{
	SetTextureManager(GetOwner()->GetRenderSystem()->GetTextureManager());
	SetTextures(m_textureName.c_str());
	GetOwner()->GetRenderSystem()->AddSpriteToBatch(this);

	SetVertexData();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);

	m_initialised = true;
}

void SpriteComponent::SetVertexData()
{
	// Bind and send data to buffer
	m_vertexBuffer = &(m_vao.GetVertexBuffer());
	m_vertexBuffer->Bind();

	Vector2 windowDimensions = GetOwner()->GetApplication()->GetWindow()->GetDimensions();

	float halfClipWidth = (GetDimensions().x / m_numFrames) / windowDimensions.x;
	float halfClipHeight = GetDimensions().y / windowDimensions.y;

	const GLfloat VERTS[] = 
	{	// position							  //texcoords
		-halfClipWidth, halfClipHeight, 0.0f, 1.0f,  0.0f, 0.0f,
		halfClipWidth, halfClipHeight, 0.0f, 1.0f,  1.0f, 0.0f,
		halfClipWidth, -halfClipHeight, 0.0f, 1.0f,  1.0f, 1.0f,

		halfClipWidth, -halfClipHeight, 0.0f, 1.0f,  1.0f, 1.0f,
		-halfClipWidth, -halfClipHeight, 0.0f, 1.0f,  0.0f, 1.0f,
		-halfClipWidth, halfClipHeight, 0.0f, 1.0f,  0.0f, 0.0f
	};

	m_vertexBuffer->SetData(sizeof(VERTS), VERTS);
}

void SpriteComponent::SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc)
{
	if(in_vertexShaderSrc.empty() || in_fragShaderSrc.empty())
		return;

	// Bind vertex array
	m_vao.Bind();

	// Bind vertex buffer
    m_vertexBuffer->Bind();

	// Create and activate shader
	m_shader.CreateShaderProgram(in_vertexShaderSrc, in_fragShaderSrc);
	m_shader.Use();

	// Add vertex attributes
	m_vertexBuffer->AddAttribute( VertexAttribute(m_shader.GetAttributeLocation("position"), 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0) );
	m_vertexBuffer->AddAttribute( VertexAttribute(m_shader.GetAttributeLocation("texcoord"), 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat))) );

	m_vao.SetVertexAttributes();

	// Add the uniforms
	AddUniforms();

	m_shader["textureSprite"]->Set(0);
}

void SpriteComponent::AddUniforms()
{
	m_shader.AddUniform("model");
	m_shader.AddUniform("frameInfo");
	m_shader.AddUniform("textureSprite");
}

void SpriteComponent::OnAttached(GameObject* in_gameObject)
{
	IRenderableComponent::OnAttached(in_gameObject);

	if(!m_initialised)
		Initialise();

	m_frameWidth = GetDimensions().x / (float)m_numFrames;
}

void SpriteComponent::OnDetached(GameObject* in_gameObject)
{
	// Fill this out with logic for anything sprite-specific that needs to be done
	IRenderableComponent::OnDetached(in_gameObject);
}

glm::mat4 SpriteComponent::CalculateModelMatrix()
{
	glm::mat4 model(1.f);
	model = glm::translate(model, GetOwner()->GetPosition()) * glm::scale(model, GetOwner()->GetScale());
	return model;
}

void SpriteComponent::Update(float in_dt)
{
	static float animTimer = 0;

	animTimer += in_dt;

	if(animTimer >= m_animSpeed)
	{
		animTimer = 0;

		if(IsAnimLooping() && m_currentFrame >= m_numFrames - 1)
			m_currentFrame = 0;
		else if(m_currentFrame < m_numFrames)
			m_currentFrame += 1;
	}
}

Vector2 SpriteComponent::GetFrameInfo()
{
	float frameWidth = GetDimensions().x / (float)m_numFrames;

	Vector2 frameInfo;
	frameInfo.x = (frameWidth * m_currentFrame) / GetDimensions().x;
	frameInfo.y = frameWidth / GetDimensions().x;

	return frameInfo;
}

/* TODO
Right now Sprites are being drawn as a square in the actual world. They should
instead be drawn last of all on top of everything else, so objects in the world
can't slice through them. This is done by disabling depth testing before drawing any sprites.

Obviously this would be needlessly expensive if meshes and sprites were mixed
up in the rendering order, so all sprites should be drawn last, in a batch.
*/
void SpriteComponent::Draw()
{
	// Set shader uniforms
	m_shader["model"]->SetMatrix(CalculateModelMatrix(), 1, GL_FALSE);
	m_shader["frameInfo"]->SetVec(GetFrameInfo(), 1);
}

const Vector2 SpriteComponent::GetDimensions()
{
	return GetTexture()->GetDimensions();
}