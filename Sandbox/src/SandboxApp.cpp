#include <TEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public TEngine::Layer
{
public:

	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.f)
	{
		m_VertexArray.reset(TEngine::VertexArray::Create()); 

		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<TEngine::VertexBuffer> vertexB;
		vertexB.reset(TEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexB->SetLayout
		(
			{
				{ TEngine::ShaderDataType::Float3, "a_Position"}, 
				{ TEngine::ShaderDataType::Float4, "a_Color"} 
			}
		);

		m_VertexArray->AddVertexBuffer(vertexB); 

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr <TEngine::IndexBuffer> indexB; 
		indexB.reset(TEngine::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t)))); 
		m_VertexArray->SetIndexBuffer(indexB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color; 

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(TEngine::Shader::Create(vertexSrc, fragmentSrc));  
	}

	void OnUpdate() override
	{
		if (TEngine::Input::IsKeyPressed(TE_KEY_LEFT))
		{
			m_CameraPosition.x += m_CameraSpeed;
		}
		if (TEngine::Input::IsKeyPressed(TE_KEY_RIGHT))
		{
			m_CameraPosition.x -= m_CameraSpeed;
		}

		if (TEngine::Input::IsKeyPressed(TE_KEY_UP))
		{
			m_CameraPosition.y -= m_CameraSpeed;
		}

		if (TEngine::Input::IsKeyPressed(TE_KEY_DOWN)) 
		{
			m_CameraPosition.y += m_CameraSpeed;
		}

		TEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		TEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition); 
		//m_Camera.SetRotation(45.f);
		TEngine::Renderer::BeginScene(m_Camera);

		TEngine::Renderer::Submit(m_Shader, m_VertexArray);

		TEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(TEngine::Event& event) override 
	{
		TEngine::EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<TEngine::KeyPressedEvent>(TE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent)); 
	}

private:

	std::shared_ptr<TEngine::Shader> m_Shader;
	std::shared_ptr <TEngine::VertexArray> m_VertexArray;

	TEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.01f;
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
