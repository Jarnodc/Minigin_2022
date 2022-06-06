#pragma once
#include "Component.h"
class MovementComponent final:  public Component
{
public:
	MovementComponent(dae::GameObject* pGO):Component(pGO){}
	~MovementComponent() override = default;

	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) noexcept = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) noexcept = delete;

	void Move(glm::vec3 moveVec);
	void Update() override{};
	void FixedUpdate() override{};
	void Render() const override{};
	enum class EDirection{Up,Down,Left,Right, Vertical, Horizontal};
	bool CanMoveTo(EDirection dir) const;
};

