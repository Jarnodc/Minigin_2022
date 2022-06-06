#include "MiniginPCH.h"
#include "Component.h"

#include "GameObject.h"

Component::~Component()
{
}

void Component::ResetComponent()
{
	GetGameObject()->SetPosition(m_SpawnPosition.x, m_SpawnPosition.y);
}

Component::Component(dae::GameObject* pGO)
	:m_pGameObject{ pGO }
	,m_SpawnPosition(pGO->GetLocalPosition())
{
}
