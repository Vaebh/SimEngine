#include "../Sound/AudioSystem.h"
#include "../Sound/Sound.h"
#include <iostream>

namespace
{
    const std::string musicPath = "../SimEngine/Assets/Audio/Music/";
    const std::string soundFXPath = "../SimEngine/Assets/Audio/Effects/";
}

AudioSystem::AudioSystem() : mNumDrivers(0), mSystem(NULL), mMusicChannelGroup(NULL), mSoundFXChannelGroup(NULL)
{

}

AudioSystem::~AudioSystem()
{
	mSystem->release();
}

void AudioSystem::Initialise()
{
	FMODErrorCheck(FMOD::System_Create(&mSystem));

	mSystem->init(512, FMOD_INIT_NORMAL, 0);

	FMODErrorCheck(mSystem->createChannelGroup("musicChannelGroup", &mMusicChannelGroup));
	FMODErrorCheck(mSystem->createChannelGroup("soundFXChannelGroup", &mSoundFXChannelGroup));

	CheckSoundcards();
}

void AudioSystem::PlaySoundEffect(const std::string& inSoundName)
{
	// TODO - Fix Memory leak
	Sound* soundEffect = new Sound(soundFXPath + inSoundName, mSystem, mSoundFXChannelGroup);
	soundEffect->Play();
}

void AudioSystem::PlayMusic(const std::string& inMusicName)
{
	// TODO - Fix Memory leak
	Sound* music = new Sound(musicPath + inMusicName, mSystem, mMusicChannelGroup);
	music->Play();
}

void AudioSystem::CheckSoundcards()
{
	FMODErrorCheck(mSystem->getNumDrivers(&mNumDrivers));

	// No sound cards (disable sound)
	if (mNumDrivers == 0)
	{
		FMODErrorCheck(mSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND));
	}
}

bool AudioSystem::FMODErrorCheck(FMOD_RESULT inResult)
{
	if (inResult != FMOD_OK)
    {
        std::cout << "FMOD error! (" << inResult << ") " << FMOD_ErrorString(inResult) << std::endl;
		return false;
    }

	return true;
}

void AudioSystem::Update(float in_dt)
{
	FMODErrorCheck(mSystem->update());
}