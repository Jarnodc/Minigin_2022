#include "MiniginPCH.h"
#include "EnemyComponent.h"

#include "BoxCollider.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "RigidBody.h"
#include "TimerInfo.h"

void EnemyComponent::Update()
{
	if(m_IsDead)
	{
		if(GetGameObject()->GetComponent<SpriteComponent>()->HasReachedEnd())
		{
			GetGameObject()->ResetObject();
			GetGameObject()->GetComponent<SpriteComponent>()->ChangeState(SpriteComponent::SpritePart(2, 1, SDL_Point{ 32,32 + static_cast<int>(m_Char) * 16 }, 16));
			GetGameObject()->GetComponent<SpriteComponent>()->SetFlip(false);
			m_IsDead = false;
			CalcClosestTarget();
		}
		return;
	}
	if(m_IsSalty)
	{
		m_CurTimer += dae::TimerInfo::GetInstance().deltaTime;
		if(m_CurTimer >= m_Timer)
		{
			m_CurTimer = 0;
			GetGameObject()->GetComponent<SpriteComponent>()->ChangeState(SpriteComponent::SpritePart(2, 1, SDL_Point{ 32,32 + static_cast<int>(m_Char) * 16 }, 16));
			GetGameObject()->GetComponent<SpriteComponent>()->SetFlip(false);
			m_IsSalty = false;
		}
		return;
	}
	if (GetGameObject()->GetParent())
	{
		return;
	}

	if (const auto pMoveComp = GetGameObject()->GetComponent<MovementComponent>())
	{
		const auto prevDir{ m_MoveDirection };
		if (pMoveComp->CanMoveTo(MovementComponent::EDirection::Vertical))
		{
			CalcMoveDirection();
		}
		else if(pMoveComp->CanMoveTo(MovementComponent::EDirection::Horizontal))
		{
			if(Magnitude<float>(GetGameObject()->GetComponent<RigidBody>()->GetVelocity()) == 0)
			{
				if (m_MoveDirection.x != 0)
					m_MoveDirection *= -1;
				else
					m_MoveDirection = {1,0,0};
			}
		}
		if(prevDir != m_MoveDirection)
		{
			if(m_MoveDirection.y < 0)
			{
				GetGameObject()->GetComponent<SpriteComponent>()->ChangeState(SpriteComponent::SpritePart(2, 1, SDL_Point{ 64,32 + static_cast<int>(m_Char) * 16 }, 16));
				GetGameObject()->GetComponent<SpriteComponent>()->SetFlip(false);
			}
			else if(m_MoveDirection.y > 0)
			{
				GetGameObject()->GetComponent<SpriteComponent>()->ChangeState(SpriteComponent::SpritePart(2, 1, SDL_Point{ 0,32 + static_cast<int>(m_Char) * 16 }, 16));
				GetGameObject()->GetComponent<SpriteComponent>()->SetFlip(false);
			}
			else if(m_MoveDirection.x < 0)
			{
				GetGameObject()->GetComponent<SpriteComponent>()->ChangeState(SpriteComponent::SpritePart(2, 1, SDL_Point{ 32,32 + static_cast<int>(m_Char) * 16 }, 16));
				GetGameObject()->GetComponent<SpriteComponent>()->SetFlip(false);
			}
			else if(m_MoveDirection.x > 0)
			{
				GetGameObject()->GetComponent<SpriteComponent>()->ChangeState(SpriteComponent::SpritePart(2, 1, SDL_Point{ 32,32 + static_cast<int>(m_Char) * 16 }, 16));
				GetGameObject()->GetComponent<SpriteComponent>()->SetFlip(true);
			}
		}
		pMoveComp->Move(m_MoveDirection);
	}
}

void EnemyComponent::FixedUpdate()
{
}

void EnemyComponent::Render() const
{
}


void EnemyComponent::ResetComponent()
{
	GetGameObject()->SetPosition(m_SpawnPosition.x, m_SpawnPosition.y);
	CalcMoveDirection();
}

void EnemyComponent::CalcMoveDirection()
{
	CalcClosestTarget();
	const auto moveComp = GetGameObject()->GetComponent<MovementComponent>();
	const auto pos{ GetGameObject()->GetLocalPosition() }, targetPos{m_pTarget->GetLocalPosition()};

	if(abs(pos.y - targetPos.y) >2 && abs(pos.x - m_PrevLadderx) > 5) // not yet on ladder and far from prev
	{
		m_PrevLadderx = pos.x;
		if(pos.y < targetPos.y && moveComp->CanMoveTo(MovementComponent::EDirection::Down)) // higher then him
		{
			m_MoveDirection = glm::vec3{ 0,1,0 };
		}
		else
		{
			m_MoveDirection = glm::vec3{ 0,-1,0 };
		}
	}
	else if (moveComp->CanMoveTo(MovementComponent::EDirection::Horizontal))
	{
		if (m_MoveDirection == glm::vec3{ 0,-1,0 } && pos.y > targetPos.y && moveComp->CanMoveTo(MovementComponent::EDirection::Up)) //going up, not yet on height and can still up
		{
			m_MoveDirection = glm::vec3{ 0,-1,0 };
		}
		else if (m_MoveDirection == glm::vec3{ 0,1,0 } && pos.y < targetPos.y && moveComp->CanMoveTo(MovementComponent::EDirection::Down))//going down, not yet on height and can still down
		{
			m_MoveDirection = glm::vec3{ 0,1,0 };
		}
		else if (m_MoveDirection.x == 0)
		{
			if (pos.x < targetPos.x && moveComp->CanMoveTo(MovementComponent::EDirection::Right))//left of him
			{
				m_MoveDirection = glm::vec3{ 1,0,0 };
			}
			else
			{
				m_MoveDirection = glm::vec3{ -1,0,0 };
			}
		}
	}
}

void EnemyComponent::CalcClosestTarget()
{
	const auto pos{ GetGameObject()->GetLocalPosition() };
	m_pTarget = m_pPlayers.front();
	assert(m_pTarget);
	int closestDist{ Magnitude<int>(m_pTarget->GetLocalPosition() - pos) };
	for (const auto& pTarget : m_pPlayers)
	{
		if(pTarget == m_pTarget)
			continue;

		const int enemyDist{ Magnitude<int>(pTarget->GetLocalPosition() - pos) };
		if(enemyDist < closestDist)
		{
			m_pTarget = pTarget;
			closestDist = enemyDist;
		}
	}
	
}
