#include "MiniginPCH.h"
#include "RigidBody.h"

#include "BoxCollider.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "TimerInfo.h"

RigidBody::RigidBody(dae::GameObject* pGO, const glm::vec3& speed)
	:Component(pGO), m_Speed(speed)
{
	m_Speed.x *= 2;
	m_Speed.y *= 2;
	m_Speed.z *= 2;
}

void RigidBody::Move(glm::vec3 moveVec)
{
	m_Velocity = moveVec * dae::TimerInfo::GetInstance().deltaTime * m_Speed;
	auto curPos = GetGameObject()->GetLocalPosition();
	curPos += m_Velocity;
	GetGameObject()->SetPosition(curPos.x, curPos.y);
}
