#pragma once
#include "Observer.h"
#include "SubjectComponent.h"

class HealthComponent final : public Observer, public SubjectComponent
{
public:
	HealthComponent(dae::GameObject* pGO);
	~HealthComponent() override = default;

	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) noexcept = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

	void Update() override{};
	void FixedUpdate() override{};
	void Render() const override{};

	void Notify(const dae::GameObject& pObject, EEvent event) override;
	int GetHealth() const { return m_Health; }
private:
	int m_Health{ 3 };
};
