#pragma once
#include "BoxCollider.h"
#include "SubjectComponent.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "RigidBody.h"

class EnemyComponent;

class IngredientComponent final:   public SubjectComponent
{
public:
	IngredientComponent(dae::GameObject* pGO);
	~IngredientComponent() override = default;

	IngredientComponent(const IngredientComponent& other) = delete;
	IngredientComponent(IngredientComponent&& other) noexcept = delete;
	IngredientComponent& operator=(const IngredientComponent& other) = delete;
	IngredientComponent& operator=(IngredientComponent&& other) noexcept = delete;
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void EnableMove()
	{
		if (const auto rigid = GetGameObject()->GetComponent<RigidBody>())
		{
			if (rigid->GetVelocity().y == 0)
			{
				const auto boxCollider = GetGameObject()->GetComponent<BoxCollider>();
				m_pPrevGroundCol = PhysicsManager::GetInstance().GetOverlappers(boxCollider,std::string("Ground")).front();
				m_Move = true;
				rigid->Move({ 0,1,0 });
			}
		}
	}
	bool Isfinished()const { return m_Finished; }
private:
	bool m_Move{ false };
	BoxCollider* m_pPrevGroundCol{ nullptr };
	bool m_Finished{ false };
	std::vector<EnemyComponent*> m_pEnemies{};
	static const int m_Cols{ 5 };
	bool m_PartDropped[m_Cols]{ false,false,false,false,false };
};

