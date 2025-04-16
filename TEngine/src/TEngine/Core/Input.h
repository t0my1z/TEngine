#pragma once

#include "Core.h"

namespace TEngine
{
	class TENGINE_API Input
	{
	public:

		inline static bool IsKeyPressed(int _keycode) { return s_Instance->IsKeyPressedImpl(_keycode); }

		inline static bool IsMouseButtonPressed(int _button) { return s_Instance->IsMouseButtonPressedImpl(_button); } 
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); } 
		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		
	protected:

		virtual bool IsKeyPressedImpl(int _keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int _button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
	private:

		static Input* s_Instance;
	};
}