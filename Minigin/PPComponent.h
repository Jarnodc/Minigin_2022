#pragma once
#include "StateMachine.h"
#include "SubjectComponent.h"
class PPComponent final:  public SubjectComponent
{
public:
	PPComponent(dae::GameObject* pGO);
	~PPComponent() override;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	void ChangeToAttack();
	

private:
	void InitStates() const;

	const size_t m_PlayerIndex;
	StateMachine* m_pSM{nullptr};

	std::shared_ptr<dae::GameObject> m_Salt{};

};

