#include "MiniginPCH.h"
#include "Achievements.h"

void Achievements::Notify(const dae::GameObject& /*gameObject*/, EEvent event)
{
	const auto it = std::find(m_UnlockedAchievments.begin(), m_UnlockedAchievments.end(), event);
	if(it == m_UnlockedAchievments.end())
	{
		Unlock(event);
	}
}

void Achievements::Unlock(EEvent achievement)
{
	m_UnlockedAchievments.push_back(achievement);

}
