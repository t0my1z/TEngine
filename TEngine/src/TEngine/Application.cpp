#include "tepch.h"
#include "Application.h"

#include "Renderer/Renderer.h"

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

		m_VertexArray.reset(VertexArray::Create());
	
		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexB;
		vertexB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexB->SetLayout
		( 
			{
				{ ShaderDataType::Float3, "a_Position"},
				{ ShaderDataType::Float4, "a_Color"}
			}
		);
		m_VertexArray->AddVertexBuffer(vertexB);

		uint32_t indices[3] = { 0, 1, 2 };   
		std::shared_ptr <IndexBuffer> indexB;
		indexB.reset(IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
		m_VertexArray->SetIndexBuffer(indexB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color; 

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"( 
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color; 
			}
		)";

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc)); 
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
			RenderCommand::Clear();

			Renderer::BeginScene(); 

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

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