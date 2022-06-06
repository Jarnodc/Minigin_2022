#pragma once
#include "InputManager.h"
#include "Singleton.h"
#include "UIButton.h"

class UIManager final: public dae::Singleton<UIManager>
{
public:
	~UIManager() override = default;

	UIManager(const UIManager& other) = delete;
	UIManager(UIManager&& other) noexcept = delete;
	UIManager& operator=(const UIManager& other) = delete;
	UIManager& operator=(UIManager&& other) noexcept = delete;

	void AddButton(UIButton* button) { m_Buttons.emplace_back(button); }
	void RemoveButton(const UIButton* button) {
		for (size_t i = 0; i < m_Buttons.size(); ++i)
		{
			if (m_Buttons.at(i) == button)
			{
				m_Buttons.erase(m_Buttons.begin() + i);
				return;
			}
		}
	}

	void HandleButtons(dae::EInputState inputState,const glm::vec2& mousePos);

private:
	friend class Singleton<UIManager>;
	UIManager() = default;

	std::vector<UIButton*> m_Buttons{};
};

