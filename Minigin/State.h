#pragma once
#include "MovementComponent.h"
#include "PhysicsManager.h"
#include "RigidBody.h"
#include "SpriteComponent.h"
#include "TimerInfo.h"

class State
{
public:
	State(dae::GameObject* pGO, SpriteComponent::SpritePart sp)
	:m_pGameObject{pGO},m_SpritePart { sp }{}
	virtual ~State() = default;

	State(const State& other) = delete;
	State(State&& other) noexcept = delete;
	State& operator=(const State& other) = delete;
	State& operator=(State&& other) noexcept = delete;
	virtual void Start()
	{
		if(const auto spriteComp = m_pGameObject->GetComponent<SpriteComponent>())
			spriteComp->ChangeState(m_SpritePart);
	}
	virtual void Execute()
	{
		
	}
protected:
	SpriteComponent::SpritePart m_SpritePart{};
	dae::GameObject* m_pGameObject{};
};
class IdleState final: public State
{
public:
	IdleState(dae::GameObject* pGO, SpriteComponent::SpritePart sp): State(pGO, sp){}
	~IdleState() override = default;

	IdleState(const IdleState& other) = delete;
	IdleState(IdleState&& other) noexcept = delete;
	IdleState& operator=(const IdleState& other) = delete;
	IdleState& operator=(IdleState&& other) noexcept = delete;

	void Execute() override
	{
		
	}
};
class MoveState final : public State
{
public:
	MoveState(dae::GameObject* pGO, SpriteComponent::SpritePart sp) : State(pGO, sp) {
	}
	~MoveState() override = default;

	MoveState(const MoveState& other) = delete;
	MoveState(MoveState&& other) noexcept = delete;
	MoveState& operator=(const MoveState& other) = delete;
	MoveState& operator=(MoveState&& other) noexcept = delete;

	void SetMovement(glm::vec3 moveVector)
	{
		m_MoveVec = moveVector;
		if (m_MoveVec.x < 0)
		{
			if (const auto spriteComp = m_pGameObject->GetComponent<SpriteComponent>())
				spriteComp->SetFlip(false);
		}
		else if (m_MoveVec.x > 0)
			if (const auto spriteComp = m_pGameObject->GetComponent<SpriteComponent>())
				spriteComp->SetFlip(true);
	}
	void Execute() override
	{

		m_pGameObject->GetComponent<MovementComponent>()->Move(m_MoveVec);
	}
private:
	glm::vec3 m_MoveVec = {};
};
class ClimbDownState final : public State
{
public:
	ClimbDownState(dae::GameObject* pGO, SpriteComponent::SpritePart sp) : State(pGO, sp) {}
	~ClimbDownState() override = default;

	ClimbDownState(const ClimbDownState& other) = delete;
	ClimbDownState(ClimbDownState&& other) noexcept = delete;
	ClimbDownState& operator=(const ClimbDownState& other) = delete;
	ClimbDownState& operator=(ClimbDownState&& other) noexcept = delete;

	void SetMovement(glm::vec3 moveVector)
	{
		m_MoveVec = moveVector;
	}
	void Execute() override
	{
		m_pGameObject->GetComponent<MovementComponent>()->Move(m_MoveVec);
	}
private:
	glm::vec3 m_MoveVec = {};
};
class ClimbUpState final : public State
{
public:
	ClimbUpState(dae::GameObject* pGO, SpriteComponent::SpritePart sp) : State(pGO, sp) {}
	~ClimbUpState() override = default;

	ClimbUpState(const ClimbUpState& other) = delete;
	ClimbUpState(ClimbUpState&& other) noexcept = delete;
	ClimbUpState& operator=(const ClimbUpState& other) = delete;
	ClimbUpState& operator=(ClimbUpState&& other) noexcept = delete;

	void SetMovement(glm::vec3 moveVector)
	{
		m_MoveVec = moveVector;
	}
	void Execute() override
	{
		m_pGameObject->GetComponent<MovementComponent>()->Move(m_MoveVec);
	}
private:
	glm::vec3 m_MoveVec = {};
};
class DieState final : public State
{
public:
	DieState(dae::GameObject* pGO, SpriteComponent::SpritePart sp) : State(pGO, sp) {}
	~DieState() override = default;

	DieState(const DieState& other) = delete;
	DieState(DieState&& other) noexcept = delete;
	DieState& operator=(const DieState& other) = delete;
	DieState& operator=(DieState&& other) noexcept = delete;

	void Execute() override
	{

	}
};
class AttackState final : public State
{
public:
	AttackState(dae::GameObject* pGO, SpriteComponent::SpritePart sp) : State(pGO, sp) {}
	~AttackState() override = default;

	AttackState(const AttackState& other) = delete;
	AttackState(AttackState&& other) noexcept = delete;
	AttackState& operator=(const AttackState& other) = delete;
	AttackState& operator=(AttackState&& other) noexcept = delete;

	void ChangeSpritePart(int offset)
	{
		m_SpritePart.SrcRect.x = offset;
		SetFlip(false);
	}

	void SetFlip(bool flip) const
	{
		if (const auto spriteComp = m_pGameObject->GetComponent<SpriteComponent>())
			spriteComp->SetFlip(flip);
	}

	void Execute() override
	{

	}
};