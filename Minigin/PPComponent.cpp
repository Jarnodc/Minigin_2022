#include "MiniginPCH.h"
#include "PPComponent.h"

#include "BoxCollider.h"
#include "EnemyComponent.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SpiceComponent.h"
#include "SpriteComponent.h"

PPComponent::PPComponent(dae::GameObject* pGO)
	:SubjectComponent(pGO)
	,m_PlayerIndex(dae::InputManager::GetInstance().AddPlayer())
	,m_pSM {new StateMachine()}
{
	InitStates();
	m_SpawnPosition = GetGameObject()->GetLocalPosition();
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_Z, std::make_shared<AttackCommand>(pGO));
}

PPComponent::~PPComponent()
{
	delete m_pSM;
	m_pSM = nullptr;
}

void PPComponent::Update()
{
	const auto bc{ GetGameObject()->GetComponent<BoxCollider>() };
	if (m_pSM->IsState<DieState>())
	{
		const auto spriteComp{ GetGameObject()->GetComponent<SpriteComponent>() };
		if(spriteComp && spriteComp->HasReachedEnd())
		{
			//Respawn
			m_pSM->ChangeState<IdleState>();
			GetSubject()->Notify(*GetGameObject(), EEvent::LoseHealth);
		}
		return;
	}
	if (bc && PhysicsManager::GetInstance().IsOverlapping(bc,std::string("Enemy")))
	{
		const auto lappers = PhysicsManager::GetInstance().GetOverlappers(bc, std::string("Enemy"));
		for(const auto& overlap: lappers)
		{
			const auto enemyComp{ overlap->GetGameObject()->GetComponent<EnemyComponent>() };
			if(!enemyComp->IsSalty() && !enemyComp->IsDead())
			{
				m_pSM->ChangeState<DieState>();
				if (m_Salt)
				{
					dae::SceneManager::GetInstance().GetScene().Remove(m_Salt);
					m_Salt.reset();
					m_Salt = nullptr;
				}
				return;
			}
		}
	}
	if(m_pSM->IsState<AttackState>())
	{
		if (m_Salt)
		{
			if (m_Salt->GetComponent<SpriteComponent>()->HasReachedEnd())
			{
				dae::SceneManager::GetInstance().GetScene().Remove(m_Salt);
				m_Salt.reset();
				m_Salt = nullptr;
				m_pSM->ChangeState<IdleState>();
			}
		}
	}
	else if (dae::InputManager::GetInstance().IsPressed(SDL_SCANCODE_A))
	{
		if (!m_pSM->IsState<MoveState>())
			m_pSM->ChangeState<MoveState>();
		m_pSM->GetState<MoveState>()->SetMovement({ -1,0,0 });
	}
	else if (dae::InputManager::GetInstance().IsPressed(SDL_SCANCODE_D))
	{
		if (!m_pSM->IsState<MoveState>())
			m_pSM->ChangeState<MoveState>();
		m_pSM->GetState<MoveState>()->SetMovement({ 1,0,0 });
	}
	else if (dae::InputManager::GetInstance().IsPressed(SDL_SCANCODE_W))
	{
		if (!m_pSM->IsState<ClimbUpState>())
			m_pSM->ChangeState<ClimbUpState>();
		m_pSM->GetState<ClimbUpState>()->SetMovement({ 0,-1,0 });
	}
	else if (dae::InputManager::GetInstance().IsPressed(SDL_SCANCODE_S))
	{
		if (!m_pSM->IsState<ClimbDownState>())
			m_pSM->ChangeState<ClimbDownState>();
		m_pSM->GetState<ClimbDownState>()->SetMovement({ 0,1,0 });
	}
	else if(!m_pSM->IsState<AttackState>())
	{
		if(!m_pSM->IsState<IdleState>())
		{
			m_pSM->ChangeState<IdleState>();
		}
	}
	m_pSM->Update();

}

void PPComponent::FixedUpdate()
{
}

void PPComponent::Render() const
{
}

void PPComponent::ChangeToAttack()
{
	if (m_pSM->IsState<AttackState>() || m_Salt)
	{
		return;
	}
	const auto salt{ std::make_shared<dae::GameObject>() };
	m_Salt = salt;
	salt->AddComponent<SpiceComponent>();
	salt->SetPosition(GetGameObject()->GetLocalPosition().x, GetGameObject()->GetLocalPosition().y);
	int offset{};
	SDL_Rect dstRect{ 0,0,20,20 };
	auto state{ m_pSM->GetState<AttackState>() };
	if (m_pSM->IsState<ClimbDownState>())
	{
		offset = 16;
		dstRect.y -= 20;
		state->ChangeSpritePart(0);
	}
	else if (m_pSM->IsState<ClimbUpState>())
	{
		offset = 32;
		dstRect.y += 20;
		state->ChangeSpritePart(32);
	}
	else if (m_pSM->IsState<MoveState>())
	{
		const auto rigidBody{ GetGameObject()->GetComponent<RigidBody>() };
		state->ChangeSpritePart(16);
		if(rigidBody->GetVelocity().x < 0)
		{
			dstRect.x -= 20;
			state->SetFlip(true);
		}
		else
		{
			dstRect.x += 20;
			state->SetFlip(false);
		}
	}
	else if (m_pSM->IsState<IdleState>())
	{
		state->ChangeSpritePart(16);
		state->SetFlip(true);
		dstRect.x += 20;
	}

	salt->AddComponent(new SpriteComponent(salt.get(), "BurgerTimeSpriteSheet.png", SpriteComponent::SpritePart(4,1,SDL_Point{ 176,16 + offset }, 16), .1f, dstRect));
	salt->AddComponent(new BoxCollider(salt.get(), dstRect));

	dae::SceneManager::GetInstance().GetScene().Add(salt);
	m_pSM->ChangeState<AttackState>();
}

void PPComponent::InitStates() const
{
	m_pSM->AddState(new IdleState(GetGameObject(), SpriteComponent::SpritePart(SDL_Point{48,16},16)));
	m_pSM->AddState(new MoveState(GetGameObject(), SpriteComponent::SpritePart(3,1, SDL_Point{48,0},16)));
	m_pSM->AddState(new DieState(GetGameObject(), SpriteComponent::SpritePart(5,1, SDL_Point{4*16,16},16)));
	m_pSM->AddState(new ClimbDownState(GetGameObject(), SpriteComponent::SpritePart(3,1, SDL_Point{0,0},16)));
	m_pSM->AddState(new ClimbUpState(GetGameObject(), SpriteComponent::SpritePart(3,1, SDL_Point{6*16,0},16)));
	m_pSM->AddState(new AttackState(GetGameObject(), SpriteComponent::SpritePart(1,1, SDL_Point{0,0},16)));
}

