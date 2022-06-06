#pragma once
#include "Component.h"
class RigidBody :
    public Component
{
public:
	RigidBody(dae::GameObject* pGO, const glm::vec3& speed);
	~RigidBody() override = default;

	RigidBody(const RigidBody& other) = delete;
	RigidBody(RigidBody&& other) noexcept = delete;
	RigidBody& operator=(const RigidBody& other) = delete;
	RigidBody& operator=(RigidBody&& other) noexcept = delete;

	void Update() override {};
	void FixedUpdate() override {};
	void Render() const override{};
	void Move(glm::vec3 moveVec);
	glm::vec3 GetVelocity()const { return m_Velocity; }
	glm::vec3 GetSpeed() const { return m_Speed; }
private:
	glm::vec3 m_Velocity{};
	glm::vec3 m_Speed{100,100,100};
};

