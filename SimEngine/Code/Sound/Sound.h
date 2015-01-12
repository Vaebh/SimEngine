#include "../Sound/AudioSystem.h"

class Sound
{
public:
	Sound(const std::string& inFilename, FMOD::System* inFMODSystem, FMOD::ChannelGroup* inChannelGroup);
	~Sound();

	void Play();
  void Stop();

	bool IsPlaying();
  bool IsPaused();
	bool IsMuted();
   
  float GetVolume();
  float GetLength();

private:
	FMOD::Sound* mSound;
	FMOD::Channel* mChannel;
	FMOD::System* mFMODSystem;
};