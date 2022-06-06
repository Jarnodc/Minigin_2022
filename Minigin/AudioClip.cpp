#include "MiniginPCH.h"
#include "AudioClip.h"

AudioClip::AudioClip(const std::string& path, int loops, int volume)
	:m_Path{path}
	,m_Volume{volume}
	,m_Loops{ loops }
{
	SetVolume(volume);
}

AudioClip::~AudioClip()
{
	std::cout << "audioClip destoyed" << std::endl;
	Mix_FreeChunk(m_pSample);
	m_pSample = nullptr;
}

//AudioClip::AudioClip(const AudioClip& other)
//{
//	m_Channel = other.m_Channel;
//	m_Path = other.m_Path;
//	m_Volume = other.m_Volume;
//	m_Loops = other.m_Loops;
//	m_pSample = other.m_pSample;
//}
//
//AudioClip::AudioClip(AudioClip&& other)
//{
//	m_Channel = other.m_Channel;
//	m_Path = other.m_Path;
//	m_Volume = other.m_Volume;
//	m_Loops = other.m_Loops;
//	m_pSample = other.m_pSample;
//}

bool AudioClip::operator==(const AudioClip& ac) const
{
	return ac.m_Loops == m_Loops && ac.m_Volume == m_Volume && ac.m_Path == m_Path;
}

bool AudioClip::LoadWav()
{
	m_pSample = Mix_LoadWAV(m_Path.c_str());
	if (m_pSample)
		return true;

	printf("Mix_LoadWAV: %s\n", Mix_GetError());
	return false;
	
}

void AudioClip::Play()
{
	m_Channel = Mix_PlayChannel(-1, m_pSample, m_Loops);
	if (m_Channel == -1)
	{
		printf("Mix_PlayChannel: %s\n", Mix_GetError());
	}
}

void AudioClip::Pause() const
{
	if (m_Channel != -1)
	{
		Mix_Pause(m_Channel);
	}
}

void AudioClip::Resume() const
{
	if (m_Channel != -1)
	{
		Mix_Resume(m_Channel);
	}
}

void AudioClip::SetVolume(const int volume)
{
	if (m_pSample)
	{
		m_Volume = Mix_VolumeChunk(m_pSample, volume);
		printf("Volume set to: %d\n", m_Volume);
	}
}

bool AudioClip::IsPlaying() const
{
	return Mix_Playing(m_Channel) == 1;
}
