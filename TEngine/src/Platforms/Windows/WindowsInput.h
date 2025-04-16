#pragma once

#include "TEngine/Core/Input.h"

namespace TEngine
{
	class WindowsInput : public Input
	{
	protected:

		virtual bool IsKeyPressedImpl(int _keycode);

		virtual bool IsMouseButtonPressedImpl(int _button) override; 
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePosImpl() override; 
	};

}