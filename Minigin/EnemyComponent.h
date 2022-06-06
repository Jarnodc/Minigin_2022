#pragma once
#include "Component.h"
#include "SpriteComponent.h"

class EnemyComponent final:  public Component
{
public:
	enum class EEnemy
	{
		Mr_HotDog = 0,Mr_Pickle = 1,Mr_Egg = 2
	};
	EnemyComponent(dae::GameObject* pGO):Component(pGO){}
	~EnemyComponent() override = default;

	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) noexcept = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;

	void SetTarget(const std::vector<dae::GameObject*>& pPlayers) { m_pPlayers = pPlayers; }
	void SetChar(EEnemy enemy) { m_Char = enemy; }
	EEnemy GetChar() const { return m_Char; }
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;
	bool IsDead() const { return m_IsDead; }
	void SetDead() {
		m_IsSalty = false;
		m_IsDead = true;
	const auto spriteComp = GetGameObject()->GetComponent<SpriteComponent>();
	auto spritePart{ spriteComp->GetSpritePart() };
	spritePart.SrcRect.y = 48;
	spritePart.SrcRect.x = 0;
	spritePart.Cols = 4;
	spritePart.StartPos = { 0,48 };
	spriteComp->ChangeState(spritePart);
	}

	void SetSalty() { m_IsSalty = true;
	const auto spriteComp = GetGameObject()->GetComponent<SpriteComponent>();
	auto spritePart{ spriteComp->GetSpritePart() };
	spritePart.SrcRect.y = 48;
	spritePart.SrcRect.x = 64;
	spritePart.Cols = 2;
	spritePart.StartPos = { 64,48 };
	spriteComp->ChangeState(spritePart);
	}
	bool IsSalty()const { return m_IsSalty; }

	void ResetComponent() override;
private:
	void CalcMoveDirection();

	void CalcClosestTarget();

	std::vector<dae::GameObject*> m_pPlayers{ nullptr };
	dae::GameObject* m_pTarget{ nullptr };
	float m_PrevLadderx{};
	glm::vec3 m_MoveDirection{ 1,0,0 };

	bool m_IsDead{ false };
	bool m_IsSalty{ false };
	float m_CurTimer{};
	float m_Timer{ 2.f };
	EEnemy m_Char{ EEnemy::Mr_Egg };
};

