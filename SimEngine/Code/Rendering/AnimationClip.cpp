#include "../Rendering/AnimationClip.h"

namespace
{
	float animTimer = 0.f;
}

AnimationClip::AnimationClip(char* in_name, const char* in_animStartImage, uint32_t in_numFrames) :
m_animationName(in_name),
m_numFrames(in_numFrames),
m_currentFrame(0),
m_animationSpeed(0.f),
m_looping(false),
m_active(false),
m_activeImage(NULL)
{
	m_animImages.reserve(m_numFrames);
}

AnimationClip::AnimationClip(char* in_name, const std::vector<Image*>& in_newImages) :
m_animImages(in_newImages),
m_animationName(in_name),
m_currentFrame(0),
m_animationSpeed(0.1f),
m_looping(false),
m_active(false),
m_activeImage(NULL)
{
	m_activeImage = m_animImages[0];
	m_numFrames = m_animImages.size();

	m_looping = true;
}

void AnimationClip::Play(bool in_looping)
{
	m_looping = in_looping;
	m_active = true;
}

void AnimationClip::Stop()
{
	m_active = false;

	animTimer = 0.f;
}

Image* AnimationClip::Update(float in_dt)
{
	animTimer += in_dt;

	if (animTimer >= m_animationSpeed)
	{
		animTimer = 0;

		if (m_looping && m_currentFrame >= m_numFrames - 1)
		{
			m_currentFrame = 0;
			m_activeImage = m_animImages[m_currentFrame];
		}
		else if (m_currentFrame < m_numFrames - 1)
		{
			m_currentFrame += 1;
			m_activeImage = m_animImages[m_currentFrame];
		}
	}

	return m_activeImage;
}