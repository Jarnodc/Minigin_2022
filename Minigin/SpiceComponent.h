#pragma once
#include "Component.h"
class SpiceComponent final:  public Component
{
public:
	SpiceComponent(dae::GameObject* pGO):Component(pGO){}
	~SpiceComponent() override = default;

	SpiceComponent(const SpiceComponent& other) = delete;
	SpiceComponent(SpiceComponent&& other) noexcept = delete;
	SpiceComponent& operator=(const SpiceComponent& other) = delete;
	SpiceComponent& operator=(SpiceComponent&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override{}
	void Render() const override{}

private:

};

