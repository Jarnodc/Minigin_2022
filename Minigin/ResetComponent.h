#pragma once
#include "Observer.h"
#include "Scene.h"

class ResetComponent final : public Observer, public Component
{
public:
	ResetComponent(dae::GameObject* pGO);
	~ResetComponent() override = default;

	ResetComponent(const ResetComponent& other) = delete;
	ResetComponent(ResetComponent&& other) noexcept = delete;
	ResetComponent& operator=(const ResetComponent& other) = delete;
	ResetComponent& operator=(ResetComponent&& other) noexcept = delete;

	void Update() override {}
	void FixedUpdate() override {}
	void Render() const override {}

	void Notify(const dae::GameObject& pObject, EEvent event) override;

	void AddObject(dae::GameObject* pObject);
	void RemoveObject(dae::GameObject* pObject);

private:
	std::vector<dae::GameObject*> m_pObjects{};
};

