#pragma once
#include "Observer.h"

class ScoreDisplayComponent final : public Observer, public Component
{
public:
	ScoreDisplayComponent(dae::GameObject* pGO) :Component(pGO), Observer() { ReadHighScore(); }
	~ScoreDisplayComponent() override { WriteHighScore(); }

	ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent(ScoreDisplayComponent&& other) noexcept = delete;
	ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) noexcept = delete;

	void Update() override{}
	void FixedUpdate() override{}
	void Render() const override{}

	void Notify(const dae::GameObject& pObject, EEvent event) override;
private:
	void ReadHighScore();
	void WriteHighScore();
	int m_Score{};
	int m_HighScore{};
};

