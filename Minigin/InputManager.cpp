#include "MiniginPCH.h"
#include "InputManager.h"
#include <backends\imgui_impl_sdl.h>

#include "SceneManager.h"
#include "UIManager.h"


bool dae::InputManager::ProcessInput()
{
	while (SDL_PollEvent(&m_Event)) {
		if (m_Event.type == SDL_QUIT)
		{
			return false;
		}
		if(m_Event.button.button == SDL_BUTTON_LEFT)
		{
			const auto mousePos = glm::vec2{ m_Event.button.x,m_Event.button.y };
			if(m_Event.button.type == SDL_MOUSEBUTTONDOWN)
			{
				UIManager::GetInstance().HandleButtons(EInputState::Down, mousePos);
			}
			else if(m_Event.button.type == SDL_MOUSEBUTTONUP)
			{
				UIManager::GetInstance().HandleButtons(EInputState::Up, mousePos);
			}
		}
		for (auto& keyCom : m_KeyBoardCommands)
		{
			switch (keyCom.state)
			{
			case EInputState::Down:
				if (m_Event.type == SDL_KEYDOWN && !keyCom.isPrevFrameDown && m_Event.key.keysym.scancode == keyCom.keyBoardButton)
				{
					keyCom.isPrevFrameDown = true;
					keyCom.command->Execute();
				}
				else if (m_Event.type == SDL_KEYUP && keyCom.isPrevFrameDown && m_Event.key.keysym.scancode == keyCom.keyBoardButton)keyCom.isPrevFrameDown = false;
				break;
			case EInputState::Pressed:
				if (m_Event.type == SDL_KEYDOWN && m_Event.key.keysym.scancode == keyCom.keyBoardButton)
				{
					keyCom.command->Execute();
				}
				break;
			case EInputState::Up:
				if (m_Event.type == SDL_KEYUP && m_Event.key.keysym.scancode == keyCom.keyBoardButton)
				{
					keyCom.command->Execute();
				}
				break;
			}
		}

		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&m_Event);
	}

	for (auto val : m_ConsoleCommands)
	{
			switch (val.state)
			{
			case EInputState::Down:
				if (IsDownThisFrame(val.controllerButton, val.controllerIdx))
					val.command->Execute();
				break;
			case EInputState::Pressed:
				if (IsPressed(val.controllerButton, val.controllerIdx))
					val.command->Execute();
				break;
			case EInputState::Up:
				if (IsUpThisFrame(val.controllerButton, val.controllerIdx))
					val.command->Execute();
				break;
			}
	}
	return true;
}

void dae::InputManager::Update() const
{
	for (const auto& controller : m_pControllers)
	{
		controller->Update();
	}
}

PlayerIndex dae::InputManager::AddPlayer()
{
	PlayerIndex idx = static_cast<int>(m_pControllers.size());
	m_pControllers.push_back(std::make_unique<Xbox360Controller>(idx));
	return idx;
}

void dae::InputManager::RemovePlayer(PlayerIndex idx)
{
	if (idx < m_pControllers.size())
	{
		for (size_t i = 0; i < m_ConsoleCommands.size(); ++i)
		{
			if(m_ConsoleCommands.at(i).controllerIdx == idx)
			{
				m_ConsoleCommands.erase(m_ConsoleCommands.begin() + i);
			}
		}
		m_pControllers.erase(m_pControllers.begin() + idx);
	}
	else
		std::cout << "Idx is too high" << std::endl;

}

bool dae::InputManager::IsPressed(Xbox360Controller::ControllerButton button, PlayerIndex controllerIdx) const
{
	return m_pControllers[controllerIdx]->IsPressed(button);
}

bool dae::InputManager::IsPressed(SDL_Scancode scancode) const
{
	
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	return state[scancode];
}

bool dae::InputManager::IsDownThisFrame(Xbox360Controller::ControllerButton button, PlayerIndex controllerIdx) const
{
	return m_pControllers[controllerIdx]->IsDown(button);
}

bool dae::InputManager::IsUpThisFrame(Xbox360Controller::ControllerButton button, PlayerIndex controllerIdx) const
{
	return m_pControllers[controllerIdx]->IsUp(button);
}

void dae::InputManager::AddCommand(Xbox360Controller::ControllerButton button, std::shared_ptr<Command> command, PlayerIndex controllerIdx, EInputState state)
{
	if(controllerIdx > m_pControllers.size())
	{
		std::cout << "You are adding a command to an no existing player" << std::endl; //todo change to a throw
		return;
	}
	ControllerCommand cc;
	cc.command = command;
	cc.controllerButton = button;
	cc.state = state;
	cc.controllerIdx = controllerIdx;
	m_ConsoleCommands.push_back(cc);
}

void dae::InputManager::AddCommand(SDL_Scancode keyBoardKey, std::shared_ptr<Command> command, EInputState state)
{
	KeyBoardCommand kc;
	kc.keyBoardButton = keyBoardKey;
	kc.command = command;
	kc.state = state;
	m_KeyBoardCommands.push_back(kc);
}

void dae::InputManager::RemoveCommand(Xbox360Controller::ControllerButton button, std::shared_ptr<Command> command, PlayerIndex controllerIdx, EInputState state)
{
	const auto len{ m_ConsoleCommands.size() };
	for (size_t i = 0; i < len; ++i)
	{
		const ControllerCommand temp = m_ConsoleCommands.at(i);
		if(temp.controllerButton == button)
		{
			if(typeid(*temp.command) == typeid(*command))
			{
				if (temp.state == state)
				{
					if(temp.controllerIdx == controllerIdx)
					{
						m_ConsoleCommands.erase(m_ConsoleCommands.begin() + i);
						return;
					}
				}
			}
		}
	}
}

void dae::InputManager::RemoveCommand(SDL_Scancode keyBoardKey, std::shared_ptr<Command> command, EInputState state)
{
	const auto len{ m_KeyBoardCommands.size() };
	for (size_t i = 0; i < len; ++i)
	{
		const KeyBoardCommand temp = m_KeyBoardCommands.at(i);
		if (temp.keyBoardButton == keyBoardKey)
		{
			if (typeid(*temp.command) == typeid(*command))
			{
				if (temp.state == state)
				{
					m_ConsoleCommands.erase(m_ConsoleCommands.begin() + i);
					return;
				}
			}
		}
	}
}

