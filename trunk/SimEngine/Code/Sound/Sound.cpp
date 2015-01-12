#include "../Sound/Sound.h"

Sound::Sound(const std::string& inFilename, FMOD::System* inFMODSystem, FMOD::ChannelGroup* inChannelGroup) : mFMODSystem(inFMODSystem)
{
	if(AudioSystem::FMODErrorCheck(mFMODSystem->createSound(inFilename.c_str(), FMOD_DEFAULT, 0, &mSound)))
     AudioSystem::FMODErrorCheck(mFMODSystem->playSound(mSound, NULL, true, &mChannel));

	mChannel->setChannelGroup(inChannelGroup);
}

Sound::~Sound()
{
  AudioSystem::FMODErrorCheck(mSound->release());
}

void Sound::Play()
{
	if(!IsPlaying())
	{
		AudioSystem::FMODErrorCheck(mFMODSystem->playSound(mSound, NULL, false, &mChannel));
	}
}

void Sound::Stop()
{
  if(mChannel)
  {
    mChannel->stop();
  }
}

bool Sound::IsPlaying()
{
	bool isPlaying = false;
	AudioSystem::FMODErrorCheck(mChannel->isPlaying(&isPlaying));

	return isPlaying && !IsPaused();
}

bool Sound::IsPaused()
{
    if(!mChannel)
        return false;
    
	bool isPaused = false;
	AudioSystem::FMODErrorCheck(mChannel->getPaused(&isPaused));

	return isPaused;
}

bool Sound::IsMuted()
{
	bool isMuted = false;
	AudioSystem::FMODErrorCheck(mChannel->getMute(&isMuted));

	return isMuted;
}