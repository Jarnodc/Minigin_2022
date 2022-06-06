#include "MiniginPCH.h"
#include "BoxCollider.h"

#include "GameObject.h"
#include "PhysicsManager.h"
#include "Renderer.h"

BoxCollider::BoxCollider(dae::GameObject* pGO, SDL_Rect rect)
    :Component(pGO)
	,m_Collider(rect)
{
    PhysicsManager::GetInstance().AddBoxCollider(this);
}

BoxCollider::BoxCollider(dae::GameObject* pGO, int size)
    :Component(pGO)
    , m_Collider({ 0, 0,size,size })
{
    PhysicsManager::GetInstance().AddBoxCollider(this);
}

BoxCollider::~BoxCollider()
{
    PhysicsManager::GetInstance().RemoveBoxCollider(this);
}

void BoxCollider::Update()
{
}

void BoxCollider::FixedUpdate()
{
}

void BoxCollider::Render() const
{/*
    const auto objPos = GetGameObject()->GetLocalPosition();
    const SDL_Rect colWorldPos { static_cast<int>(m_Collider.x + objPos.x),static_cast<int>(m_Collider.y + objPos.y),m_Collider.w,m_Collider.h };
    dae::Renderer::GetInstance().RenderRectangle(colWorldPos);*/
}

bool BoxCollider::IsOverlapping(const BoxCollider* collider, bool includeBorder) const
{
    const auto objPos = GetGameObject()->GetLocalPosition();
    const SDL_Rect colWorldPos{ static_cast<int>(m_Collider.x + objPos.x),static_cast<int>(m_Collider.y + objPos.y),m_Collider.w,m_Collider.h };

    const auto otherObjPos = collider->GetGameObject()->GetLocalPosition();
    const SDL_Rect other = collider->GetBoxCollider();
    const SDL_Rect otherColPos{ static_cast<int>(other.x + otherObjPos.x),static_cast<int>(other.y + otherObjPos.y),other.w,other.h };

    const SDL_Point l1{ otherColPos.x,otherColPos.y + otherColPos.h }, r1{ otherColPos.x + otherColPos.w, otherColPos.y  };
    const SDL_Point l2{ colWorldPos.x,colWorldPos.y + colWorldPos.h }, r2{ colWorldPos.x + colWorldPos.w, colWorldPos.y  };

    if (includeBorder)
		return !(l1.x > r2.x || l2.x > r1.x || l1.y < r2.y || l2.y < r1.y);
	return !(l1.x >= r2.x || l2.x >= r1.x || l1.y <= r2.y || l2.y <= r1.y);
}

bool BoxCollider::IsOverlapping(BoxCollider* collider, bool includeBorder, std::string tag) const
{
    return IsOverlapping(collider,includeBorder) && GetGameObject()->GetTag() == tag;
}

bool BoxCollider::IsOverlapping(BoxCollider* collider, std::string tag) const
{
    return IsOverlapping(collider) && GetGameObject()->GetTag() == tag;
}
