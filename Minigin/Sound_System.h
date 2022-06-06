#pragma once
using SoundID = unsigned int;

#include <string>
#include <thread>

class SoundSystem
{
public:
	SoundSystem() = default;
	virtual ~SoundSystem() = default;

	SoundSystem(const SoundSystem& other) = delete;
	SoundSystem(SoundSystem&& other) noexcept = delete;
	SoundSystem& operator=(const SoundSystem& other) = delete;
	SoundSystem& operator=(SoundSystem&& other) noexcept = delete;

	virtual void AddToQueue(const std::string& , int  = 0, int  = 50) = 0;
	virtual void AddToQueue(const std::string& , int ) = 0;
	 
	virtual void CheckQueue() = 0;
	virtual void StopQueue() = 0;
private:
};



#pragma region EmptySoundSystem
class Empty_Sound_System final : public SoundSystem
{
public:
	Empty_Sound_System() = default;
	~Empty_Sound_System() override = default;

	Empty_Sound_System(const Empty_Sound_System& other) = delete;
	Empty_Sound_System(Empty_Sound_System&& other) noexcept = delete;
	Empty_Sound_System& operator=(const Empty_Sound_System& other) = delete;
	Empty_Sound_System& operator=(Empty_Sound_System&& other) noexcept = delete;

	void AddToQueue(const std::string&, int  = 0, int  = 50)override {}
	void AddToQueue(const std::string&, int )override {}

	void CheckQueue() override {}
	void StopQueue() override {};
};
#pragma endregion
#pragma region SDL_SoundSystem
class SDLSoundSystem final : public SoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem() override;

	SDLSoundSystem(const SDLSoundSystem& other) = delete;
	SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
	SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
	SDLSoundSystem& operator=(SDLSoundSystem&& other) noexcept = delete;

	void AddToQueue(const std::string& filename, int loops = 0, int volume = 50)override;
	void AddToQueue(const std::string& filename, int volume)override { AddToQueue(filename, 0, volume); }

	void CheckQueue() override;
	void StopQueue() override;
private:
	class SoundSystemImpl;
	SoundSystemImpl* m_pImpl{ nullptr };
	std::thread m_thread;
};
#pragma endregion