#pragma once
#include "GameObject.h"
#include "PPComponent.h"

class Command
{
public:
	explicit Command(dae::GameObject* gameObject);
	virtual ~Command() = default;
	virtual void Execute() = 0;

	Command(const Command& other) = delete;
	Command(Command&& other) noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) noexcept = delete;
protected:
	dae::GameObject* GetObject() const;
	dae::GameObject* m_pGameObject = nullptr;
private:
};
class AttackCommand final : public Command
{
public:
	explicit AttackCommand(dae::GameObject* gameObject):Command(gameObject){}
	~AttackCommand() override = default;
	virtual void Execute()
	{
		m_pGameObject->GetComponent<PPComponent>()->ChangeToAttack();
	}

	AttackCommand(const AttackCommand& other) = delete;
	AttackCommand(AttackCommand&& other) noexcept = delete;
	AttackCommand& operator=(const AttackCommand& other) = delete;
	AttackCommand& operator=(AttackCommand&& other) noexcept = delete;
private:
};