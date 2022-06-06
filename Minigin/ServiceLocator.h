#pragma once
#include "Sound_System.h"

class ServiceLocator final
{
	static SoundSystem* m_pSsInstance;
	static Empty_Sound_System m_defaultSs;
public:
	static SoundSystem& GetSoundSystem();
	static void RegisterSoundSystem(SoundSystem* ss);
	static void ReleaseSoundSystem();
	ServiceLocator() = delete;
	~ServiceLocator() = delete;

	ServiceLocator(const ServiceLocator& other) = delete;
	ServiceLocator(ServiceLocator&& other) noexcept = delete;
	ServiceLocator& operator=(const ServiceLocator& other) = delete;
	ServiceLocator& operator=(ServiceLocator&& other) noexcept = delete;
};
