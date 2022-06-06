#include "MiniginPCH.h"
#include "ScoreDisplayComponent.h"

#include <fstream>

#include "TextComponent.h"

void ScoreDisplayComponent::Notify(const dae::GameObject& , EEvent event)
{
	switch (event)
	{
	case EEvent::Score50:
		m_Score += 50;
		break;
	case EEvent::Score100:
		m_Score += 100;
		break;
	case EEvent::Score200:
		m_Score += 200;
		break;
	case EEvent::Score300:
		m_Score += 300;
		break;
	case EEvent::Score500:
		m_Score += 500;
		break;
	case EEvent::Score1000:
		m_Score += 1000;
		break;
	case EEvent::Score2000:
		m_Score += 2000;
		break;
	case EEvent::Score4000:
		m_Score += 4000;
		break;
	case EEvent::Score8000:
		m_Score += 8000;
		break;
	case EEvent::Score16000:
		m_Score += 16000;
		break;
	case EEvent::Die:
		WriteHighScore();
		m_Score = 0;
		break;
	}
	if (m_HighScore < m_Score)
		GetGameObject()->GetComponent<dae::TextComponent>()->SetText("HighScore: " + std::to_string(m_Score));
}
void ScoreDisplayComponent::ReadHighScore()
{
	std::ifstream highScore;
	highScore.open("../Data/HighScore.SIIUUU", std::ios::in);
	if(!highScore)
	{
		GetGameObject()->GetComponent<dae::TextComponent>()->SetText("HighScore: " + std::to_string(m_HighScore));
		highScore.close();
		return;
	}
	highScore >> m_HighScore;
	
	highScore.close();
	GetGameObject()->GetComponent<dae::TextComponent>()->SetText("HighScore: " + std::to_string(m_HighScore));

}
void ScoreDisplayComponent::WriteHighScore()
{

	std::ofstream highScore;
	highScore.open("../Data/HighScore.SIIUUU");
	
		if (m_HighScore < m_Score)
			m_HighScore = m_Score;

		highScore << m_HighScore;

		highScore.close();
	

}

