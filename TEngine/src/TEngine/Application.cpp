#include "tepch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"

namespace TEngine
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());  
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}