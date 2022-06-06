#include "MiniginPCH.h"
#include "Transform.h"

#include "GameObject.h"

void dae::Transform::UpdateWorldPosition()
{
	if(m_PositionIsDirty)
	{
		m_PositionIsDirty = false;
		if (m_pOwner)
			m_WorldPosition = m_pOwner->GetWorldPosition() + m_LocalPosition;
		else
			m_WorldPosition = m_LocalPosition;

	}
}

const glm::vec3& dae::Transform::GetLocalPosition() const
{
	return m_LocalPosition;
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;

	m_PositionIsDirty = true;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;

	m_PositionIsDirty = true;
}

void dae::Transform::SetDirty() 
{
	m_PositionIsDirty = true;
}

dae::Transform::Transform(dae::GameObject* pGO)
	:m_pOwner(pGO)
{
}

dae::Transform::~Transform()
{
}
