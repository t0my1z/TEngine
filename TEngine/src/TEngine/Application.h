#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace TEngine
{
	class TENGINE_API Application
	{
		public:

		Application();
		virtual ~Application(); 

		void Run();

		void OnEvent(Event& _event);

		void PushLayer(Layer* _layer);
		void PushOverlay(Layer* _overlay); 

		static inline Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClosed(WindowCloseEvent& _event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack; 

	private:

		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}

