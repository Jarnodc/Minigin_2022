#pragma once
#include "BoxCollider.h"
#include "Singleton.h"

class PhysicsManager final: public dae::Singleton<PhysicsManager>
{
public:
	~PhysicsManager() override = default;

	PhysicsManager(const PhysicsManager& other) = delete;
	PhysicsManager(PhysicsManager&& other) noexcept = delete;
	PhysicsManager& operator=(const PhysicsManager& other) = delete;
	PhysicsManager& operator=(PhysicsManager&& other) noexcept = delete;

	void AddBoxCollider(BoxCollider* bc) { m_Colliders.emplace_back(bc); }
	void RemoveBoxCollider(const BoxCollider* bc) {
		for (size_t i = 0; i < m_Colliders.size(); ++i)
		{
			if (m_Colliders.at(i) == bc)
			{
				m_Colliders.erase(m_Colliders.begin() + i);
				return;
			}
		}
	}

	std::vector<BoxCollider*> GetColliders(std::string tag) const;
	std::vector<BoxCollider*> GetOverlappers(BoxCollider* bc, bool includeBorders = false) const;
	std::vector<BoxCollider*> GetOverlappers(BoxCollider* bc, bool includeBorders, std::string tag) const;
	std::vector<BoxCollider*> GetOverlappers(BoxCollider* bc, std::string tag) const;

	bool IsOverlapping(BoxCollider* bc, bool includeBorders = false) const;
	bool IsOverlapping(BoxCollider* bc, bool includeBorders, std::string tag) const;
	bool IsOverlapping(BoxCollider* bc, std::string tag) const;
private:
	friend class Singleton<PhysicsManager>;
	PhysicsManager() = default;
	std::vector<BoxCollider*> m_Colliders{};
};

