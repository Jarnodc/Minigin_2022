#pragma once

namespace dae
{
	class GameObject;
}
//class Collider;
class Component
{
public:
	virtual ~Component();

	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render() const = 0;

	//virtual void IsOverLapping(Collider collider) const = 0;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void ResetComponent();

	dae::GameObject* GetGameObject()const { return m_pGameObject; }
private:
	dae::GameObject* m_pGameObject;
protected:
	glm::vec2 m_SpawnPosition;
	explicit Component(dae::GameObject* pGO);
};

