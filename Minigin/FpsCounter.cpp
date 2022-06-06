#include "MiniginPCH.h"
#include "FpsCounter.h"
#include "TimerInfo.h"

dae::FpsCounter::~FpsCounter()
{
}

void dae::FpsCounter::Update()
{
	const float dt{ dae::TimerInfo::GetInstance().deltaTime};
	m_Frames += dt;
	if (m_Frames >= m_SecPerUpdate)
	{
		const int fps = static_cast<int>(1 / dt);
		auto textObject = GetGameObject()->GetComponent<TextComponent>();
		if (textObject)
			textObject->SetText(std::to_string(fps));
		m_Frames -= m_SecPerUpdate;
	}
}
void dae::FpsCounter::FixedUpdate()
{
}

void dae::FpsCounter::Render() const
{
}

