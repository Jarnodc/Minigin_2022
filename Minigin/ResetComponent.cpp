#include "MiniginPCH.h"
#include "ResetComponent.h"

#include "SceneManager.h"

ResetComponent::ResetComponent(dae::GameObject* pGO)
	:Component(pGO)
	,Observer()
{
}

void ResetComponent::Notify(const dae::GameObject& , EEvent event)
{
	switch (event)
	{
	case EEvent::Reset:
		for (const auto& pObject : m_pObjects)
		{
			pObject->ResetObject();
		}
		break;
	case EEvent::Die:
		m_pObjects.clear();
		dae::SceneManager::GetInstance().LoadScene("Level01" );
		break;
	}
}

void ResetComponent::AddObject(dae::GameObject* pObject)
{
	m_pObjects.emplace_back(pObject);
}

void ResetComponent::RemoveObject(dae::GameObject* pObject)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(),m_pObjects.end(),pObject));
}
