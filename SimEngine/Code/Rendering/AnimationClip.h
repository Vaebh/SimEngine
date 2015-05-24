#ifndef ANIMATION_CLIP_SIMENGINE
#define ANIMATION_CLIP_SIMENGINE

#include "../Foundation/Foundation.h"

#include "../Rendering/Image.h"

#include <vector>
#include <memory>

class AnimationClip
{
public:
	AnimationClip(char* in_name, const char* in_animStartImage, int in_numFrames);
	AnimationClip(char* in_name, std::vector<Image*>& out_newImages);

	void SetAnimImages(const std::vector<Image*>& in_newImages);

	inline char* GetName() { return m_animationName; }
	inline void SetName(char* in_animationName) { m_animationName = in_animationName; }

	inline float GetDuration() { return m_duration; }
	void SetDuration(float in_duration);

	inline float GetSpeed() { return m_animationSpeed; }
	inline void SetSpeed(float in_animationSpeed) { m_animationSpeed = in_animationSpeed; }

	inline bool IsLooping() { return m_looping; }
	inline void SetLooping(bool in_looping) { m_looping = in_looping; }

	inline bool IsActive() { return m_active; }
	inline void SetActive(bool in_active) { m_active = in_active; }

	void Play(bool in_looping);
	void Stop();
	void Reset();

	Image* Animate(float in_dt);

private:
	char* m_animationName;

	float m_animTimer;
	float m_duration;
	float m_animStep;
	float m_animationSpeed;

	uint32_t m_numFrames;
	int m_currentFrame;

	bool m_active;
	bool m_looping;

	Image* m_activeImage;
	std::vector< std::unique_ptr<Image> > m_animImages;
};

#endif