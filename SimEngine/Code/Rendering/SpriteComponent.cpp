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
	const std::string DEFAULT_VERT_SHADER = "../SimEngine/Assets/Shaders/2DVertexShaderDefaultPacked.txt";
	const std::string DEFAULT_FRAG_SHADER = "../SimEngine/Assets/Shaders/2DFragShaderDefaultPacked.txt";

	const std::vector<Vector4> vertPositions
	{
		Vector4(-1.0f, 1.0f, 0.0f, 1.f),
		Vector4(1.0f, 1.0f, 0.0f, 1.f),
		Vector4(1.0f, -1.0f, 0.0f, 1.f),
		Vector4(1.0f, -1.0f, 0.0f, 1.f),
		Vector4(-1.0f, -1.0f, 0.0f, 1.f), 
		Vector4(-1.0f, 1.0f, 0.0f, 1.f)
	};

	const std::vector<Vector2> texPositions
	{
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(0.0f, 1.0f),
		Vector2(0.0f, 0.0f)
	};
}

SpriteComponent::SpriteComponent(const std::string in_imageName) :
IRenderableComponent(),
m_activeImage(NULL),
m_imageName(in_imageName),
m_uvs(),
m_initialised(false),
m_imageScale(),
m_activeAnimation(NULL),
m_defaultAnimation(NULL)
{

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

	GetOwner()->GetRenderSystem()->AddComponent(this);

	SetVertexData();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);

	m_initialised = true;
}

bool SpriteComponent::SetImages()
{
	Image* const newImage = RequestImage(m_imageName.c_str());

	if (newImage != NULL)
		m_activeImage = newImage;

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
	// Get buffer
	m_vertexBuffer = &(m_vao.GetVertexBuffer());
}

void SpriteComponent::SetShader(const std::string in_vertexShaderSrc, const std::string in_fragShaderSrc)
{
	if(in_vertexShaderSrc.empty() || in_fragShaderSrc.empty())
		return;

	// Create and activate shader
	m_shader.CreateShaderProgram(in_vertexShaderSrc, in_fragShaderSrc);
	m_shader.Use();
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

	Vector3 adjustedPos = GetOwner()->GetPosition();
	adjustedPos *= Vector3(Application::GetApplication()->GetWindow()->GetSpriteScaler(), 1.f);
	adjustedPos += Vector3(-1.f, 1.f, 0.f);

	model = glm::translate(model, adjustedPos) * glm::scale(model, GetOwner()->GetScale()) * glm::scale(model, m_imageScale);
	return model;
}

void SpriteComponent::Update(float in_dt)
{
	if (m_activeAnimation != NULL && m_activeAnimation->IsActive())
		m_activeImage = m_activeAnimation->Animate(in_dt);
	else if (m_defaultAnimation != NULL)
	{
		if (m_activeAnimation != NULL && m_activeAnimation != m_defaultAnimation)
			m_activeAnimation->Reset();

		m_activeAnimation = m_defaultAnimation;
		m_activeImage = m_defaultAnimation->Animate(in_dt);
	}
}

void SpriteComponent::GetVertexInfo(std::vector<GLfloat>& out_vertInfo)
{
	Vector4 spriteInfo = GetFrameInfo();

	for (int i = 0; i < vertPositions.size(); ++i)
	{
		Vector4 posVec = CalculateModelMatrix() * vertPositions[i];

		out_vertInfo.push_back(posVec.x);
		out_vertInfo.push_back(posVec.y);
		out_vertInfo.push_back(posVec.z);
		out_vertInfo.push_back(1.f); // w

		out_vertInfo.push_back(texPositions[i].x);
		out_vertInfo.push_back(texPositions[i].y);

		out_vertInfo.push_back(spriteInfo.x);
		out_vertInfo.push_back(spriteInfo.y);
		out_vertInfo.push_back(spriteInfo.z);
		out_vertInfo.push_back(spriteInfo.w);
	}
}

glm::vec4 SpriteComponent::GetFrameInfo()
{
	glm::vec4 theFrameInfo = glm::vec4(m_activeImage->GetUVs(), m_activeImage->GetPercentOfTexture());
	return theFrameInfo;
}

void SpriteComponent::PreDraw()
{
	GetOwner()->GetRenderSystem()->AddSpriteToBatch(this);
}

void SpriteComponent::Draw()
{
	
}

const std::string SpriteComponent::GetTextureName()
{
	return GetTexture()->GetName();
}

bool SpriteComponent::SetDefaultAnimationClip(const char* in_animName)
{
	if (m_animationClips[in_animName].get() == NULL)
		return false;

	m_defaultAnimation = m_animationClips[in_animName].get();

	return true;
}

bool SpriteComponent::PlayAnimationClip(const char* in_animName)
{
	if (m_animationClips[in_animName].get() == NULL)
		return false;

	m_activeAnimation = m_animationClips[in_animName].get();

	return true;
}

void SpriteComponent::AddAnimation(char* in_animName, float in_duration, bool in_looping, uint32_t in_numFrames, char* in_startImage)
{
	std::vector<Image*> requestedImages;

	Image* const newImage = RequestImage(in_startImage);

	if (newImage != nullptr)
	{
		requestedImages.push_back(newImage);
		AnimationClip* animClip = new AnimationClip(in_animName, requestedImages);
		m_animationClips[in_animName].reset(animClip);
	}

	/*std::vector<Image*> requestedImages;

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
	}*/
}

void SpriteComponent::AddAnimation(char* in_animName, float in_duration, bool in_looping, uint32_t in_numFrames, ...)
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
		animClip->SetDuration(in_duration);
		animClip->SetLooping(in_looping);
		m_animationClips[in_animName].reset(animClip);
	}
}

void SpriteComponent::AddAnimation(AnimationClip* in_animationClip)
{
	if (in_animationClip != NULL)
		m_animationClips[in_animationClip->GetName()].reset(in_animationClip);
}

AnimationClip* SpriteComponent::GetAnimationClip(const char* in_animName)
{
	return m_animationClips[in_animName].get();
}