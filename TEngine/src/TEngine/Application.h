#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "TEngine/ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack; 

		unsigned int m_VertexArray; 
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr <VertexBuffer> m_VertexBuffer;
		std::unique_ptr <IndexBuffer> m_IndexBuffer;  
	private:

		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}

