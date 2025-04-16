#include "tepch.h"
#include "WindowsInput.h"
#include "TEngine/Core/Application.h"
#include "TEngine/Core/Window.h"
#include <GLFW/glfw3.h>

namespace TEngine
{
	Input* Input::s_Instance = new WindowsInput();  

	bool WindowsInput::IsKeyPressedImpl(int _keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()); 
		int state = glfwGetKey(window, _keycode); 

		return state == GLFW_PRESS || state == GLFW_REPEAT; 
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int _button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, _button);
		return state == GLFW_PRESS; 
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return (float)x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return (float)y;  
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}
}