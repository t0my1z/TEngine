#include "tepch.h"
#include "Application.h"

namespace TEngine
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());  
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent)); 
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& _event)
	{
		EventDispatcher dispatcher(_event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed)); 

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(_event);
			if (_event.Handled())
				break;
		}
	}

	void Application::PushLayer(Layer* _layer)
	{
		m_LayerStack.PushLayer(_layer);
	}

	void Application::PushOverlay(Layer* _overlay)
	{
		m_LayerStack.PushOverlay(_overlay);
	}

	bool Application::OnWindowClosed(WindowCloseEvent& _event)
	{
		m_Running = false;
		return true;
	}
}