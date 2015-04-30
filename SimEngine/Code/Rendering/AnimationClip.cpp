#include "../Rendering/AnimationClip.h"

AnimationClip::AnimationClip(char* in_name, std::vector<Image*>& out_newImages) :
m_animationName(in_name),
m_currentFrame(0),
m_animTimer(0.f),
m_duration(1.f),
m_looping(false),
m_active(true),
m_activeImage(NULL),
m_animStep(0.f),
m_animationSpeed(1.f)
{
	if (!out_newImages.empty())
	{
		for (int i = 0; i < out_newImages.size(); ++i)
		{
			m_animImages.push_back(std::unique_ptr<Image>(out_newImages[i]));
		}

		m_activeImage = m_animImages[0].get();
		m_numFrames = m_animImages.size();

		m_animStep = m_duration / m_numFrames;
	}
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

void AnimationClip::SetDuration(float in_duration)
{
	if (in_duration >= 0)
		m_duration = in_duration;
	else
		m_duration = 0.f;

	m_animStep = m_duration / m_numFrames;
}

Image* AnimationClip::Animate(float in_dt)
{
	if (m_active && !m_animImages.empty())
	{
		m_animTimer += in_dt * m_animationSpeed;

		m_currentFrame = (int)(m_animTimer / m_animStep);

		if (abs(m_currentFrame) >= m_numFrames)
		{
			m_animTimer = 0.f;
			m_currentFrame = 0;

			if (!m_looping)
				m_active = false;
		}

		if (m_currentFrame < 0)
			m_currentFrame = m_numFrames + m_currentFrame;

		m_activeImage = m_animImages[m_currentFrame].get();
	}

	return m_activeImage;
}