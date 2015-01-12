#include "../Rendering/AnimatedSpriteComponent.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(const std::string inTexture, int inNumFrames, float inAnimationSpeed, bool inbLooping) : SpriteComponent(inTexture),
mAnimSpeed(inAnimationSpeed),
mNumFrames(inNumFrames),
mCurrentFrame(0),
mAnimating(true),
mAnimTimer(0),
mLooping(inbLooping)
{
    SendAnimInfo();
}

void AnimatedSpriteComponent::Play(bool inbLooping)
{
    mLooping = inbLooping;
    mAnimating = true;
}

void AnimatedSpriteComponent::Stop()
{
    mAnimating = false;
}
 
void AnimatedSpriteComponent::ChangeFrame()
{
	if(mCurrentFrame < mNumFrames - 1)
		mCurrentFrame += 1;
	else
	{
		mCurrentFrame = 0;

		if(!mLooping)
		{
			Stop();
		}
	}

	SendAnimInfo();
}
 
void AnimatedSpriteComponent::SendAnimInfo()
{
    float spriteFrameDivisorX = 1.f / mNumFrames;

	glUseProgram(mShader.GetProgramID());
      
	glUniform2f(GetUVUniform(), spriteFrameDivisorX, 1.f);
    glUniform1i(GetFrameUniform(), mCurrentFrame);
}
 
void AnimatedSpriteComponent::Update(float inDT)
{
	SpriteComponent::Update(inDT);

	if(mAnimating)
	{
		mAnimTimer += inDT;
      
		if(mAnimTimer >= mAnimSpeed)
		{
			mAnimTimer = 0;
			ChangeFrame();
		}
	}
}

void AnimatedSpriteComponent::Draw()
{
	SpriteComponent::Draw();
	SendAnimInfo();
}