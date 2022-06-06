#include "MiniginPCH.h"
#include "IngredientComponent.h"

#include "EnemyComponent.h"
#include "SceneManager.h"


IngredientComponent::IngredientComponent(dae::GameObject* pGO)
	:SubjectComponent(pGO)
{
}

void IngredientComponent::Update()
{
	if (m_Finished)
		return;
	if(const auto boxCollider = GetGameObject()->GetComponent<BoxCollider>())
	{
		if(PhysicsManager::GetInstance().IsOverlapping(boxCollider,std::string("Player")) && !m_Move)
		{
			m_pPrevGroundCol = PhysicsManager::GetInstance().GetOverlappers(boxCollider, std::string("Ground"))[0];
			const auto player = PhysicsManager::GetInstance().GetOverlappers(boxCollider, std::string("Player"))[0];
			const auto ppos = player->GetGameObject()->GetLocalPosition();
			const float dist{ (ppos.x + player->GetBoxCollider().w / 2)- GetGameObject()->GetLocalPosition().x};
			if (dist < 0 || dist > boxCollider->GetBoxCollider().w)
				return;
			const int nr = static_cast<int>(dist / (boxCollider->GetBoxCollider().w / m_Cols));
			if(!m_PartDropped[nr])
			{
				m_PartDropped[nr] = true;
				bool fullDown = true;
				for (size_t i = 0; i < m_Cols; i++)
				{
					if(!m_PartDropped[i])
					{
						fullDown = false;
						break;
					}
				}
				if(fullDown)
				{
					GetSubject()->Notify(*GetGameObject(), EEvent::Score50);
					m_Move = true;
					for (size_t i = 0; i < m_Cols; i++)
					{
						m_PartDropped[nr] = false;
					}
				}
			}
		}
		if (m_Move)
		{
			if(const auto rigid = GetGameObject()->GetComponent<RigidBody>())
			{
				rigid->Move({ 0,1,0 });
			}
			const auto overlappers = PhysicsManager::GetInstance().GetOverlappers(boxCollider);
			for (const auto& overlapper : overlappers)
			{
				if(overlapper == m_pPrevGroundCol)
					continue;
				if(overlapper->GetGameObject()->GetTag() == "Ground")
				{
					m_pPrevGroundCol = overlapper;
					m_Move = false;
					break;
				}
				if (overlapper->GetGameObject()->GetTag() == "Ingredient")
				{
					const auto ingredient = overlapper->GetGameObject()->GetComponent<IngredientComponent>();
					if (ingredient->Isfinished())
					{
						m_Finished = true;
						const auto ings = PhysicsManager::GetInstance().GetColliders("Ingredient");
						for(const auto ing : ings)
						{
							if (!ing->GetGameObject()->GetComponent<IngredientComponent>()->Isfinished())
							{
								return;
							}
						}
						++dae::SceneManager::GetInstance().idxNextScene;
						if (dae::SceneManager::GetInstance().idxNextScene == 4)
							dae::SceneManager::GetInstance().idxNextScene = 1;
						dae::SceneManager::GetInstance().LoadScene("Level0" + std::to_string(dae::SceneManager::GetInstance().idxNextScene));
					}
					else
						ingredient->EnableMove();
				}
				else if (overlapper->GetGameObject()->GetTag() == "Plate")
				{
					m_Finished = true;
					const auto ings = PhysicsManager::GetInstance().GetColliders("Ingredient");
					for (const auto ing : ings)
					{
						if (!ing->GetGameObject()->GetComponent<IngredientComponent>()->Isfinished())
						{
							return;
						}
					}
					++dae::SceneManager::GetInstance().idxNextScene;
					if (dae::SceneManager::GetInstance().idxNextScene == 4)
						dae::SceneManager::GetInstance().idxNextScene = 1;
					dae::SceneManager::GetInstance().LoadScene("Level0" + std::to_string(dae::SceneManager::GetInstance().idxNextScene));
				}
				else if (overlapper->GetGameObject()->GetTag() == "Enemy")
				{
					const auto pEnemyComp = overlapper->GetGameObject()->GetComponent<EnemyComponent>();
					const auto pos{ pEnemyComp->GetGameObject()->GetLocalPosition() },oPos{GetGameObject()->GetLocalPosition()};

					for (const auto enemy : m_pEnemies)
					{
						if (enemy == pEnemyComp)
							return;
					}
					if(pos.y > oPos.y)
					{
						pEnemyComp->SetDead();
						switch (pEnemyComp->GetChar())
						{
						case EnemyComponent::EEnemy::Mr_HotDog:
							GetSubject()->Notify(*GetGameObject(), EEvent::Score100);
							break;
						case EnemyComponent::EEnemy::Mr_Pickle:
							GetSubject()->Notify(*GetGameObject(), EEvent::Score200);
							break;
						case EnemyComponent::EEnemy::Mr_Egg:
							GetSubject()->Notify(*GetGameObject(), EEvent::Score300);
							break;
						}
					}
					else
					{
						const auto bc{ boxCollider->GetBoxCollider() };
						pEnemyComp->GetGameObject()->SetPosition(oPos.x + bc.x + bc.w / 2.f, oPos.y + bc.y * 1.f - 20);
						GetGameObject()->AddChild(pEnemyComp->GetGameObject());
						m_pEnemies.emplace_back(pEnemyComp);
					}
				}
			}
		}
		else
		{
			if(!m_pEnemies.empty())
			{
				switch (m_pEnemies.size())
				{
				case 1:
					GetSubject()->Notify(*GetGameObject(), EEvent::Score500);
					break;
				case 2:
					GetSubject()->Notify(*GetGameObject(), EEvent::Score1000);
					break;
				case 3:
					GetSubject()->Notify(*GetGameObject(), EEvent::Score2000);
					break;
				case 4:
					GetSubject()->Notify(*GetGameObject(), EEvent::Score4000);
					break;
				case 5:
					GetSubject()->Notify(*GetGameObject(), EEvent::Score8000);
					break;
				case 6:
					GetSubject()->Notify(*GetGameObject(), EEvent::Score16000);
					break;
				}
			}
			for (size_t i = 0; i < m_pEnemies.size(); i++)
			{
				if(!m_pEnemies[i]->IsDead())
				{
					m_pEnemies[i]->SetDead();
					switch (m_pEnemies[i]->GetChar())
					{
					case EnemyComponent::EEnemy::Mr_HotDog:
						GetSubject()->Notify(*GetGameObject(), EEvent::Score100);
						break;
					case EnemyComponent::EEnemy::Mr_Pickle:
						GetSubject()->Notify(*GetGameObject(), EEvent::Score200);
						break;
					case EnemyComponent::EEnemy::Mr_Egg:
						GetSubject()->Notify(*GetGameObject(), EEvent::Score300);
						break;
					}
					GetGameObject()->RemoveChild(m_pEnemies[i]->GetGameObject());
					m_pEnemies.erase(std::ranges::remove(m_pEnemies, m_pEnemies[i]).begin());
				}
				else
				{
					m_pEnemies.erase(std::ranges::remove(m_pEnemies,m_pEnemies[i]).begin());
				}
			}
			if (const auto rigid = GetGameObject()->GetComponent<RigidBody>())
			{
				rigid->Move({ 0,0,0 });
			}
		}
	}
}

void IngredientComponent::FixedUpdate()
{
}

void IngredientComponent::Render() const
{
}
