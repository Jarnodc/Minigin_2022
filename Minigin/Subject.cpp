#include "MiniginPCH.h"
#include "Subject.h"

void Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void Subject::RemoveObserver(Observer* pObserver)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(),pObserver));
}

void Subject::Notify(const dae::GameObject& gameObject, EEvent event) const
{
	for (const auto& pObserver : m_pObservers)
	{
		pObserver->Notify(gameObject, event);
	}
}
