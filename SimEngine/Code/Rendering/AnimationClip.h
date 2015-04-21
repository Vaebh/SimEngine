#ifndef ANIMATION_CLIP_SIMENGINE
#define ANIMATION_CLIP_SIMENGINE

#include "../Foundation/Foundation.h"

#include "../Rendering/Image.h"

#include <vector>
#include <memory>

class AnimationClip
{
public:
	AnimationClip(char* in_name, const char* in_animStartImage, uint32_t in_numFrames);
	AnimationClip(char* in_name, std::vector<Image*>& out_newImages);

	void SetAnimImages(const std::vector<Image*>& in_newImages);
	inline void SetAnimationSpeed(float in_animSpeed) { m_animationSpeed = in_animSpeed; }

	void Play(bool in_looping);
	void Stop();

	Image* Animate(float in_dt);

private:
	char* m_animationName;

	float m_animTimer;
	float m_animationSpeed;

	uint32_t m_numFrames;
	uint32_t m_currentFrame;

	bool m_active;
	bool m_looping;

	Image* m_activeImage;
	std::vector< std::unique_ptr<Image> > m_animImages;
};

#endif