#include "MiniginPCH.h"
#include "UIManager.h"

void UIManager::HandleButtons(dae::EInputState inputState, const glm::vec2& mousePos)
{
	for (const auto& button : m_Buttons)
	{
		switch (inputState)
		{
		case dae::EInputState::Down:
			button->ButtonDown(mousePos);
			break;
		case dae::EInputState::Up:
			button->ButtonUp(mousePos);
			break;
		}
	}
}
