#include "../Rendering/SpriteComponent.h"

#include "../Application/Application.h"

#include "../Debug/Log.h"

#include "../Foundation/Foundation.h"
#include "../Foundation/StringUtils.h"

#include "../OpenGL/GLUtils.h"

#include "../Rendering/Image.h"
#include "../Rendering/RenderSystem.h"
#include "../Rendering/Texture.h"

#include "../Structure/GameObject.h"
#include "../Structure/Window.h"

namespace
{
	const std::string DEFAULT_VERT_SHADER = "../SimEngine/Assets/Shaders/2DVertexShaderDefault.txt";
	const std::string DEFAULT_FRAG_SHADER = "../SimEngine/Assets/Shaders/2DFragShaderDefault.txt";
}

SpriteComponent::SpriteComponent(const std::string in_imageName, const uint32_t in_numFrames) :
IRenderableComponent(),
m_activeImage(NULL),
m_imageName(in_imageName),
m_numFrames(in_numFrames),
m_currentFrame(0),
m_frameWidth(0),
m_animSpeed(0.1f),
m_loopAnim(true),
m_uvs(Vector2(0)),
m_initialised(false)
{
	m_imageFrames.reserve(m_numFrames);
}

SpriteComponent::~SpriteComponent()
{
	m_vao.Destroy();
}

void SpriteComponent::Initialise()
{
	SetTextureManager(GetOwner()->GetRenderSystem()->GetTextureManager());
	SetImages();
	GetOwner()->GetRenderSystem()->AddSpriteToBatch(this);

	SetVertexData();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);

	m_initialised = true;
}

void SpriteComponent::SetImages()
{
	for(int i = 0; i < m_numFrames; ++i)
	{
		Image* newImage = RequestImage((m_imageName + ConvertNumber(i + 1)).c_str());

		if(newImage != NULL)
			m_imageFrames.push_back(newImage);
		else
		{
			Log().Get() << m_numFrames << " sprite frames requested, only " << i << " frames found.";
			m_numFrames = i;
		}
	}

	if(!m_imageFrames.empty())
		m_activeImage = m_imageFrames[0];
}

void SpriteComponent::SetVertexData()
{
	// Bind and send data to buffer
	m_vertexBuffer = &(m_vao.GetVertexBuffer());
	m_vertexBuffer->Bind();

	Vector2 windowDimensions = GetOwner()->GetApplication()->GetWindow()->GetDimensions();

	float halfClipWidth = (m_activeImage->GetTexture()->GetDimensions().x / m_numFrames) / windowDimensions.x;
	float halfClipHeight = m_activeImage->GetTexture()->GetDimensions().y / windowDimensions.y;

	/*const GLfloat VERTS[] = 
	{	// position							  //texcoords
		-halfClipWidth, halfClipHeight, 0.0f, 1.0f,  0.0f, 0.0f,
		halfClipWidth, halfClipHeight, 0.0f, 1.0f,  1.0f, 0.0f,
		halfClipWidth, -halfClipHeight, 0.0f, 1.0f,  1.0f, 1.0f,

		halfClipWidth, -halfClipHeight, 0.0f, 1.0f,  1.0f, 1.0f,
		-halfClipWidth, -halfClipHeight, 0.0f, 1.0f,  0.0f, 1.0f,
		-halfClipWidth, halfClipHeight, 0.0f, 1.0f,  0.0f, 0.0f
	};*/

	const GLfloat VERTS[] = 
	{	// position							  //texcoords
		-0.5, 0.5, 0.0f, 1.0f,  0.0f, 0.0f,
		0.5, 0.5, 0.0f, 1.0f,  1.0f, 0.0f,
		0.5, -0.5, 0.0f, 1.0f,  1.0f, 1.0f,

		0.5, -0.5, 0.0f, 1.0f,  1.0f, 1.0f,
		-0.5, -0.5, 0.0f, 1.0f,  0.0f, 1.0f,
		-0.5, 0.5, 0.0f, 1.0f,  0.0f, 0.0f
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
	m_shader.AddUniform("spriteFrame");
	m_shader.AddUniform("textureSprite");
}

void SpriteComponent::OnAttached(GameObject* in_gameObject)
{
	IRenderableComponent::OnAttached(in_gameObject);

	if(!m_initialised)
		Initialise();

	m_frameWidth = m_activeImage->GetDimensions().x / (float)m_numFrames;
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
	// TODO - Redo this whole animation thing to work with separate images instead of the same texture
	static float animTimer = 0;

	animTimer += in_dt;

	if(animTimer >= m_animSpeed)
	{
		animTimer = 0;

		if(IsAnimLooping() && m_currentFrame >= m_numFrames - 1)
		{
			m_currentFrame = 0;
			m_activeImage = m_imageFrames[m_currentFrame];
		}
		else if(m_currentFrame < m_numFrames)
		{
			m_currentFrame += 1;
			m_activeImage = m_imageFrames[m_currentFrame];
		}
	}
}
#include "../Debug/Log.h"
glm::vec4 SpriteComponent::GetFrameInfo()
{
	float frameWidth = m_activeImage->GetDimensions().x / (float)m_numFrames;

	Vector2 frameInfo;
	frameInfo.x = (frameWidth * m_currentFrame) / m_activeImage->GetDimensions().x;
	frameInfo.y = frameWidth / m_activeImage->GetDimensions().x;

	//return frameInfo;

	/*Vector2 uvs;

	m_imageFrames[m_currentFrame-1]->GetUVs();*/

	//Log().Get() << "m_activeImage->GetUVs().x: " << m_activeImage->GetUVs().x;
	//Log().Get() << "m_activeImage->GetUVs().y: " << m_activeImage->GetUVs().y;

	
	Vector2 widthHeight;
	widthHeight.x = m_activeImage->GetDimensions().x / GetTexture()->GetDimensions().x;
	widthHeight.y = m_activeImage->GetDimensions().y / GetTexture()->GetDimensions().y;

	glm::vec4 theFrameInfo = glm::vec4(m_activeImage->GetUVs(), widthHeight);
	return theFrameInfo;//m_activeImage->GetUVs();
	//return Vector2(0,0);
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
	//m_shader.Use();
	//m_texture->Activate(GL_TEXTURE0);
	//m_texture->Bind();

	//m_vao.Bind();

	// Set shader uniforms
	m_shader["model"]->SetMatrix(CalculateModelMatrix(), 1, GL_FALSE);
	m_shader["spriteFrame"]->SetVec(GetFrameInfo(), 1);

	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

const std::string SpriteComponent::GetTextureName()
{
	return GetTexture()->GetName();
}