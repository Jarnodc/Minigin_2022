#include "MiniginPCH.h"
#include "Command.h"

Command::Command(dae::GameObject* gameObject)
	:m_pGameObject(gameObject)
{
}

dae::GameObject* Command::GetObject() const
{
	return m_pGameObject;
}
