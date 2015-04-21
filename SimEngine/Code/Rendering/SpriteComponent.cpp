#include "../Rendering/SpriteComponent.h"

#include "../Application/Application.h"

#include "../Debug/Log.h"

#include "../Foundation/Foundation.h"
#include "../Foundation/StringUtils.h"

#include "../OpenGL/GLUtils.h"

#include "../Rendering/AnimationClip.h"
#include "../Rendering/Image.h"
#include "../Rendering/RenderSystem.h"
#include "../Rendering/Texture.h"

#include "../Structure/GameObject.h"
#include "../Structure/Window.h"

#include <cstdarg>

namespace
{
	const std::string DEFAULT_VERT_SHADER = "../SimEngine/Assets/Shaders/2DVertexShaderDefault.txt";
	const std::string DEFAULT_FRAG_SHADER = "../SimEngine/Assets/Shaders/2DFragShaderDefault.txt";

	const GLfloat VERTS[] =
	{	// position				//texcoords
		-1.0, 1.0, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0, 1.0, 0.0f, 1.0f, 1.0f, 0.0f,
		1.0, -1.0, 0.0f, 1.0f, 1.0f, 1.0f,

		1.0, -1.0, 0.0f, 1.0f, 1.0f, 1.0f,
		-1.0, -1.0, 0.0f, 1.0f, 0.0f, 1.0f,
		-1.0, 1.0, 0.0f, 1.0f, 0.0f, 0.0f
	};

	float animTimer = 0.f;
}

SpriteComponent::SpriteComponent(const std::string in_imageName, const uint32_t in_numFrames) :
IRenderableComponent(),
m_activeImage(NULL),
m_imageName(in_imageName),
m_numFrames(in_numFrames),
m_currentFrame(0),
m_animSpeed(0.1f),
m_loopAnim(true),
m_uvs(),
m_initialised(false),
m_imageScale(),
m_activeAnimation(NULL)
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
	if (!SetImages())
		return;
	GetOwner()->GetRenderSystem()->AddSpriteToBatch(this);

	SetVertexData();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);

	m_initialised = true;
}

bool SpriteComponent::SetImages()
{
	if (m_numFrames == 1)
	{
		Image* const newImage = RequestImage(m_imageName.c_str());

		if (newImage != NULL)
			m_activeImage = newImage;
	}
	else
	{
		for(int i = 0; i < m_numFrames; ++i)
		{
			Image* const newImage = RequestImage((m_imageName + ConvertNumber(i + 1)).c_str());

			if(newImage != NULL)
				m_imageFrames.push_back(newImage);
			else
			{
				Log().Get() << m_numFrames << " sprite frames requested, only " << i << " frames found.";
				m_numFrames = i;
				break;
			}
		}

		if (!m_imageFrames.empty())
		{
			m_activeImage = m_imageFrames[0];
		}
	}

	if (m_activeImage != NULL)
		SetImageScale();
	else
		return false;
}

void SpriteComponent::SetImageScale()
{
	Vector2 windowDimensions = GetOwner()->GetApplication()->GetWindow()->GetDimensions();

	float clipWidth = m_activeImage->GetDimensions().x / windowDimensions.x;
	float clipHeight = m_activeImage->GetDimensions().y / windowDimensions.y;

	m_imageScale = Vector3(clipWidth, clipHeight, 1.f);
}

void SpriteComponent::SetVertexData()
{
	// Bind and send data to buffer
	m_vertexBuffer = &(m_vao.GetVertexBuffer());
	m_vertexBuffer->Bind();

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
}

void SpriteComponent::OnDetached(GameObject* in_gameObject)
{
	// Fill this out with logic for anything sprite-specific that needs to be done
	IRenderableComponent::OnDetached(in_gameObject);
}

glm::mat4 SpriteComponent::CalculateModelMatrix()
{
	glm::mat4 model(1.f);

	model = glm::translate(model, GetOwner()->GetPosition()) * glm::scale(model, GetOwner()->GetScale()) * glm::scale(model, m_imageScale);
	return model;
}

void SpriteComponent::Update(float in_dt)
{
	if (m_activeAnimation != NULL)
		m_activeImage = m_activeAnimation->Animate(in_dt);
}

glm::vec4 SpriteComponent::GetFrameInfo()
{
	glm::vec4 theFrameInfo = glm::vec4(m_activeImage->GetUVs(), m_activeImage->GetPercentOfTexture());
	return theFrameInfo;
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

bool SpriteComponent::SetActiveAnimation(const char* in_animName)
{
	if (m_animationClips[in_animName].get() == NULL)
		return false;

	m_activeAnimation = m_animationClips[in_animName].get();

	return true;
}

void SpriteComponent::AddAnimation(char* in_animName, uint32_t in_numFrames, char* in_startImage)
{
	std::vector<Image*> requestedImages;

	for (int i = 0; i < in_numFrames; ++i)
	{
		Image* const newImage = RequestImage((in_startImage + ConvertNumber(i + 1)).c_str());

		if (newImage != NULL)
			requestedImages.push_back(newImage);
		else
		{
			Log().Get() << in_numFrames << " anim frames requested, only " << i << " frames found.";
			in_numFrames = i;
			break;
		}
	}

	if (!requestedImages.empty())
	{
		AnimationClip* animClip = new AnimationClip(in_animName, requestedImages);
		m_animationClips[in_animName].reset(animClip);
	}
}

void SpriteComponent::AddAnimation(char* in_animName, uint32_t in_numFrames, ...)
{
	va_list args;
	va_start(args, in_numFrames);

	std::vector<Image*> requestedImages;

	for (int i = 0; i < in_numFrames; ++i)
	{
		const char* imgName = va_arg(args, const char*);
		Image* const reqImage = m_texManager->RequestImage(imgName);

		if (reqImage != NULL)
			requestedImages.push_back(reqImage);
	}

	va_end(args);

	if (!requestedImages.empty())
	{
		AnimationClip* animClip = new AnimationClip(in_animName, requestedImages);
		m_animationClips[in_animName].reset(animClip);
	}
}