#pragma once
#include "Command.h"
#include "Singleton.h"
#include "Xbox360Controller.h"
#define PlayerIndex unsigned int
namespace dae
{
	enum class EMouseButton
	{
		Left,Middle,Right
	};
	enum class EInputState
	{
		Down,
		Pressed,
		Up
	};
	struct ControllerCommand
	{
		ControllerCommand() = default;
		Xbox360Controller::ControllerButton controllerButton{};
		EInputState state{};
		std::shared_ptr<Command> command{};
		PlayerIndex controllerIdx{};
	};
	struct KeyBoardCommand
	{
		KeyBoardCommand() = default;
		SDL_Scancode keyBoardButton{};
		EInputState state{};
		std::shared_ptr<Command> command{};
		bool isPrevFrameDown{ false };
	};
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		bool ProcessInput();
		void Update() const;

		PlayerIndex AddPlayer();
		void RemovePlayer(PlayerIndex idx);

		bool IsPressed(Xbox360Controller::ControllerButton button, PlayerIndex controllerIdx) const;
		bool IsPressed(SDL_Scancode scancode) const;
		bool IsDownThisFrame(Xbox360Controller::ControllerButton button, PlayerIndex controllerIdx) const;
		bool IsUpThisFrame(Xbox360Controller::ControllerButton button, PlayerIndex controllerIdx) const;
		

		void AddCommand(Xbox360Controller::ControllerButton button, std::shared_ptr<Command> command, PlayerIndex controllerIdx, EInputState state = EInputState::Down);
		void AddCommand(SDL_Scancode keyBoardKey, std::shared_ptr<Command> command, EInputState state = EInputState::Down);

		void RemoveCommand(Xbox360Controller::ControllerButton button, std::shared_ptr<Command> command, PlayerIndex controllerIdx, EInputState state = EInputState::Down);
		void RemoveCommand(SDL_Scancode keyBoardKey, std::shared_ptr<Command> command, EInputState state = EInputState::Down);

	private:
		std::vector<KeyBoardCommand> m_KeyBoardCommands{};
		SDL_Event m_Event{};
		std::vector<ControllerCommand> m_ConsoleCommands{};
		std::vector<std::unique_ptr<Xbox360Controller>> m_pControllers{};
	};

}
