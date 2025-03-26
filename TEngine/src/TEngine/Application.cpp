#include "tepch.h"
#include "Application.h"

#include <glad/glad.h>

namespace TEngine
{
	Application* Application::s_Instance = nullptr; 

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType _type)
	{
		switch (_type) 
		{
			case TEngine::ShaderDataType::None:		break; 
			case TEngine::ShaderDataType::Float:	return GL_FLOAT;
			case TEngine::ShaderDataType::Float2:	return GL_FLOAT; 
			case TEngine::ShaderDataType::Float3:	return GL_FLOAT; 
			case TEngine::ShaderDataType::Float4:	return GL_FLOAT; 
			case TEngine::ShaderDataType::Mat3:		return GL_FLOAT;  
			case TEngine::ShaderDataType::Mat4:		return GL_FLOAT; 
			case TEngine::ShaderDataType::Int:		return GL_INT; 
			case TEngine::ShaderDataType::Int2:		return GL_INT; 
			case TEngine::ShaderDataType::Int3:		return GL_INT; 
			case TEngine::ShaderDataType::Int4:		return GL_INT; 
			case TEngine::ShaderDataType::Bool:		return GL_BOOL; 
		}

		TE_CORE_ASSERT(false, "Unknown ShaderDataType"); 
		return 0;
	}

	Application::Application()
	{
		TE_CORE_ASSERT(!s_Instance, "Application Already Exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());  
		m_Window->SetEventCallback(TE_BIND_EVENT_FN(Application::OnEvent)); 

		m_ImGuiLayer = new ImGuiLayer();   
		PushOverlay(m_ImGuiLayer);  

		//Vertex array
		//Vertex buffer
		//shader
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
	
		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices))); 

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
				{ ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		for (const auto& element : m_VertexBuffer->GetLayout()) 
		{
			glEnableVertexAttribArray(index); 
			glVertexAttribPointer(
				index, element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				m_VertexBuffer->GetLayout().GetStride(), 
				(const void*)element.Offset
			);
			++index; 
		}

		uint32_t indices[3] = { 0, 1, 2 };  
		m_IndexBuffer.reset(IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));   

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
			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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