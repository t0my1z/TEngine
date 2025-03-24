#include "tepch.h"
#include "WindowsWindow.h"

namespace TEngine
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& _props)
	{
		return new WindowsWindow(_props); 
	}

	WindowsWindow::WindowsWindow(const WindowProps& _props)
	{
		Init(_props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown(); 
	}

	void WindowsWindow::SetVSync(bool _enabled)
	{
		if (_enabled)
			glfwSwapInterval(1); 
		else
			glfwSwapInterval(0); 

		m_Data.m_VSync = _enabled;  
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.m_VSync; 
	}

	void WindowsWindow::Init(const WindowProps& _props)
	{
		m_Data.m_Title = _props.m_Title;
		m_Data.m_Height = _props.m_Height;
		m_Data.m_Width = _props.m_Width;

		TE_CORE_INFO("Creating Window {0} ({1}, {2})", _props.m_Title, _props.m_Width, _props.m_Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();

			TE_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true; 
		}

		m_Window = glfwCreateWindow((int)_props.m_Width, (int)_props.m_Height, m_Data.m_Title.c_str(), nullptr, nullptr); 
		glfwMakeContextCurrent(m_Window); 
		glfwSetWindowUserPointer(m_Window, &m_Data); 
		SetVSync(true); 
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window); 
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents(); 
		glfwSwapBuffers(m_Window);  
	}

}