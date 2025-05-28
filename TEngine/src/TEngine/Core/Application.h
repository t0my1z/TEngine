#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "TEngine/Events/Event.h" 
#include "TEngine/Events/ApplicationEvent.h"

#include "TEngine/Core/Timestep.h"

#include "TEngine/ImGui/ImGuiLayer.h"

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
		bool OnWindowResize(WindowResizeEvent& _event); 

	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false; 
		LayerStack m_LayerStack; 
		float m_LastFrameTime = 0.0f; 
	private:

		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}

