#include "../Rendering/AnimationClip.h"

AnimationClip::AnimationClip(char* in_name, std::vector<Image*>& out_newImages) :
m_animationName(in_name),
m_currentFrame(0),
m_animTimer(0.f),
m_animationSpeed(0.1f),
m_looping(false),
m_active(false),
m_activeImage(NULL)
{
	for (int i = 0; i < out_newImages.size(); ++i)
	{
		m_animImages.push_back(std::unique_ptr<Image>(out_newImages[i]));
	}

	m_activeImage = m_animImages[0].get();
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

	m_animTimer = 0.f;
}

Image* AnimationClip::Animate(float in_dt)
{
	m_animTimer += in_dt;

	if (m_animTimer >= m_animationSpeed)
	{
		m_animTimer = 0;

		if (m_looping && m_currentFrame >= m_numFrames - 1)
		{
			m_currentFrame = 0;
			m_activeImage = m_animImages[m_currentFrame].get();
		}
		else if (m_currentFrame < m_numFrames - 1)
		{
			m_currentFrame += 1;
			m_activeImage = m_animImages[m_currentFrame].get();
		}
	}

	return m_activeImage;
}