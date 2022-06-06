#pragma once
#include "Singleton.h"
#include "ResourceManager.h"
namespace dae
{
	class TimerInfo final : public Singleton<TimerInfo>
	{
	public:
		const float fixedTimeStep = 0.02f;
		float deltaTime = 0.f;
	private:
		friend class Singleton<ResourceManager>;
	};
}