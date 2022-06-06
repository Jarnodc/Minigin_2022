#pragma once
#include <XInput.h>

namespace dae
{
	class Xbox360Controller final
	{
		class Xbox360ControllerImpl;
		Xbox360ControllerImpl* m_pImpl = nullptr;
	public:
		enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ButtonDPADUp = XINPUT_GAMEPAD_DPAD_UP,
		ButtonDPADDown = XINPUT_GAMEPAD_DPAD_DOWN,
		ButtonDPADLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonDPADRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonBack = XINPUT_GAMEPAD_BACK,
		ButtonLeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		ButtonRightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		ButtonLeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		ButtonRightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	};
		void Update() const;

		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;

		explicit Xbox360Controller(int controllerIdx);
		~Xbox360Controller();

	};
}
