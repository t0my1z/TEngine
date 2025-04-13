#include <TEngine.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Platforms/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public TEngine::Layer
{
public:

	ExampleLayer() 
		: 
		Layer("Example"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.f),
		m_TrianglePosition(1.0f),
		m_TriangleColor({0.2f, 0.3f, 0.8f})
	{
		m_VertexArray.reset(TEngine::VertexArray::Create()); 

		float vertices[9] = {
			-0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};

		TEngine::Ref<TEngine::VertexBuffer> vertexB;
		vertexB.reset(TEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexB->SetLayout
		(
			{
				{ TEngine::ShaderDataType::Float3, "a_Position"}
			}
		);

		m_VertexArray->AddVertexBuffer(vertexB); 

		uint32_t indices[3] = { 0, 1, 2 };
		TEngine::Ref<TEngine::IndexBuffer> indexB;
		indexB.reset(TEngine::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t)))); 
		m_VertexArray->SetIndexBuffer(indexB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"( 
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1); 
			}
		)";

		m_Shader.reset(TEngine::Shader::Create(vertexSrc, fragmentSrc));  
	}

	void OnUpdate(TEngine::Timestep ts) override 
	{
		//TE_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		#pragma region Input Test

		if (TEngine::Input::IsKeyPressed(TE_KEY_RIGHT)) 
		{
			m_CameraPosition.x += m_CameraSpeed * ts; 
		}
		if (TEngine::Input::IsKeyPressed(TE_KEY_LEFT))  
		{
			m_CameraPosition.x -= m_CameraSpeed * ts; 
		}

		if (TEngine::Input::IsKeyPressed(TE_KEY_DOWN)) 
		{
			m_CameraPosition.y -= m_CameraSpeed * ts; 
		}
		if (TEngine::Input::IsKeyPressed(TE_KEY_UP))  
		{
			m_CameraPosition.y += m_CameraSpeed * ts; 
		}

		if (TEngine::Input::IsKeyPressed(TE_KEY_D))  
		{
			m_TrianglePosition.x += m_CameraSpeed * ts;
		}
		if (TEngine::Input::IsKeyPressed(TE_KEY_A))    
		{
			m_TrianglePosition.x -= m_CameraSpeed * ts;
		}

		if (TEngine::Input::IsKeyPressed(TE_KEY_S))  
		{
			m_TrianglePosition.y -= m_CameraSpeed * ts; 
		}
		if (TEngine::Input::IsKeyPressed(TE_KEY_W))  
		{
			m_TrianglePosition.y += m_CameraSpeed * ts; 
		}

		#pragma endregion

		TEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		TEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition); 
		//m_Camera.SetRotation(45.f);

		TEngine::Renderer::BeginScene(m_Camera);

		m_Shader->Bind(); 
		std::dynamic_pointer_cast<TEngine::OpenGLShader>(m_Shader)->
			UploadUniformFloat3("u_Color", m_TriangleColor); 

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_TrianglePosition); 
		TEngine::Renderer::Submit(m_Shader, m_VertexArray, transform); 

		TEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("TriangleColor", glm::value_ptr(m_TriangleColor)); 
		ImGui::End(); 
	}

	void OnEvent(TEngine::Event& event) override 
	{
		TEngine::EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<TEngine::KeyPressedEvent>(TE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent)); 
	}

private:

	TEngine::Ref<TEngine::Shader> m_Shader;
	TEngine::Ref<TEngine::VertexArray> m_VertexArray;

	TEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.0f;

	glm::vec3 m_TrianglePosition;
	glm::vec3 m_TriangleColor;  
};

class Sandbox : public TEngine::Application
{
public:

	Sandbox()
	{
		PushLayer(new ExampleLayer());  
	}

	~Sandbox()
	{

	}
};
 
TEngine::Application* TEngine::CreateApplication()
{
	return new Sandbox(); 
}
