#include "MiniginPCH.h"
#include "PhysicsManager.h"

#include "GameObject.h"

std::vector<BoxCollider*> PhysicsManager::GetColliders(std::string tag) const
{
	std::vector<BoxCollider*> bcs{};
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol->GetGameObject()->GetTag() == tag)
			bcs.emplace_back(boxCol);
	}
	return bcs;
}

std::vector<BoxCollider*> PhysicsManager::GetOverlappers(BoxCollider* bc, bool includeBorders) const
{
	std::vector<BoxCollider*> bcs{};
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, includeBorders))
		{
			bcs.emplace_back(boxCol);
		}
	}
	return bcs;
}

std::vector<BoxCollider*> PhysicsManager::GetOverlappers(BoxCollider* bc, bool includeBorders, std::string tag) const
{
	std::vector<BoxCollider*> bcs{};
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, includeBorders,tag))
		{
			bcs.emplace_back(boxCol);
		}
	}
	return bcs;
}

std::vector<BoxCollider*> PhysicsManager::GetOverlappers(BoxCollider* bc, std::string tag) const
{
	std::vector<BoxCollider*> bcs{};
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, tag))
		{
			bcs.emplace_back(boxCol);
		}
	}
	return bcs;
}

bool PhysicsManager::IsOverlapping(BoxCollider* bc, bool includeBorders) const
{
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, includeBorders))
			return true;
	}
	return false;
}

bool PhysicsManager::IsOverlapping(BoxCollider* bc, bool includeBorders, std::string tag) const
{
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, includeBorders,tag))
			return true;
	}
	return false;
}

bool PhysicsManager::IsOverlapping(BoxCollider* bc, std::string tag) const
{
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, tag))
			return true;
	}
	return false;
}
