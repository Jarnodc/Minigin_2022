#pragma once
#include <string>
#include "SDL_mixer.h"

class AudioClip final
{
private:
	std::string m_Path;
	int m_Volume;
	int m_Loops;
	int m_Channel;
	Mix_Chunk* m_pSample = nullptr;
public:
	explicit AudioClip(const std::string& path, int loops, int volume);
	~AudioClip();

	AudioClip(const AudioClip& other) = delete;
	AudioClip(AudioClip&& other) = delete;
	AudioClip& operator=(const AudioClip& other) = delete;
	AudioClip& operator=(AudioClip&& other) noexcept = delete;
	bool operator==(const AudioClip&) const;

	bool LoadWav();

	void Play();
	void Pause() const;
	void Resume() const;
	void SetVolume(const int volume);
	bool IsPlaying() const;
};
