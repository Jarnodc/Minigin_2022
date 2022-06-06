#include "MiniginPCH.h"
#include "SpiceComponent.h"

#include "BoxCollider.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "SpriteComponent.h"

void SpiceComponent::Update()
{
	if(const auto bc{ GetGameObject()->GetComponent<BoxCollider>() }; PhysicsManager::GetInstance().IsOverlapping(bc,std::string("Enemy")))
	{
		const auto overlappers{ PhysicsManager::GetInstance().GetOverlappers(bc,std::string("Enemy")) };
		for(const auto& overlapper : overlappers)
		{
			const auto pEnemyComp{ overlapper->GetGameObject()->GetComponent<EnemyComponent>() };
			if(!pEnemyComp->IsSalty())
			{
				pEnemyComp->SetSalty();
			}
		}
	}
}
