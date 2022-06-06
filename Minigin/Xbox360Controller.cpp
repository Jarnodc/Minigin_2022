#include "MiniginPCH.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib,"xinput.lib")

#include "Xbox360Controller.h"

using namespace dae;

class Xbox360Controller::Xbox360ControllerImpl
{
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	int m_ControllerIdx{};
	WORD m_ButtonsIsPressedThisFrame{};
	WORD m_ButtonsIsReleasedThisFrame{};
public:
	Xbox360ControllerImpl(int controllerIdx)
		:m_ControllerIdx(controllerIdx)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	}
	void Update()
	{
		m_PreviousState = m_CurrentState;
		//CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIdx, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsIsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsIsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}
	bool IsPressed(Xbox360Controller::ControllerButton button) const
	{
		return m_CurrentState.Gamepad.wButtons & static_cast<unsigned>(button);
	}

	bool IsDown(Xbox360Controller::ControllerButton button) const
	{
		return m_ButtonsIsPressedThisFrame & static_cast<unsigned>(button);
	}

	bool IsUp(Xbox360Controller::ControllerButton button) const
	{
		return m_ButtonsIsReleasedThisFrame & static_cast<unsigned>(button);
	}

};

void dae::Xbox360Controller::Update() const
{
	m_pImpl->Update();
}

bool dae::Xbox360Controller::IsDown(Xbox360Controller::ControllerButton button) const
{
	return m_pImpl->IsDown(button);
}

bool dae::Xbox360Controller::IsUp(Xbox360Controller::ControllerButton button) const
{
	return m_pImpl->IsUp(button);
}

bool dae::Xbox360Controller::IsPressed(Xbox360Controller::ControllerButton button) const
{
	return m_pImpl->IsPressed(button);
}

dae::Xbox360Controller::Xbox360Controller(int controllerIdx)
	:m_pImpl{ new Xbox360ControllerImpl(controllerIdx) }
{
}

dae::Xbox360Controller::~Xbox360Controller()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}
