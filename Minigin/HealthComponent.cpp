#include "MiniginPCH.h"
#include "HealthComponent.h"

#include "TextComponent.h"

HealthComponent::HealthComponent(dae::GameObject* pGO)
	:SubjectComponent(pGO)
	,Observer()
{
}

void HealthComponent::Notify(const dae::GameObject& pObject, EEvent event)
{
	if(event == EEvent::LoseHealth)
	{
		--m_Health;
		pObject.GetComponent<dae::TextComponent>()->SetText(std::to_string(m_Health));
		GetSubject()->Notify(*GetGameObject(), EEvent::Reset);
		if(m_Health == 0)
		{
			GetSubject()->Notify(pObject, EEvent::Die);
		}
	}
}
