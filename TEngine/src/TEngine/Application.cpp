#include "tepch.h"
#include "Application.h"

namespace TEngine
{


	Application* Application::s_Instance = nullptr; 

	Application::Application()
	{
		TE_CORE_ASSERT(!s_Instance, "Application Already Exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());  
		m_Window->SetEventCallback(TE_BIND_EVENT_FN(Application::OnEvent)); 

		m_ImGuiLayer = new ImGuiLayer();   
		PushOverlay(m_ImGuiLayer);  
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

			m_ImGuiLayer->Begin(); 
			for (Layer* layer : m_LayerStack) 
			{
				layer->OnImGuiRender();  
			}
			m_ImGuiLayer->End(); 
			 
			m_Window->OnUpdate(); 
		}
	}

	void Application::OnEvent(Event& _event)
	{
		EventDispatcher dispatcher(_event);
		dispatcher.Dispatch<WindowCloseEvent>(TE_BIND_EVENT_FN(Application::OnWindowClosed)); 

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
		_layer->OnAttach();
	}

	void Application::PushOverlay(Layer* _overlay)
	{
		m_LayerStack.PushOverlay(_overlay);
		_overlay->OnAttach();  
	}

	bool Application::OnWindowClosed(WindowCloseEvent& _event)
	{
		m_Running = false;
		return true;
	}
}