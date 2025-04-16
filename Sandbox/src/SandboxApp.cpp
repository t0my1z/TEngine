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
		m_CameraController(1280.0f / 720.0f), 
		m_TriangleSpeed(1), 
		m_TrianglePosition(0.f),
		m_TriangleColor({0.2f, 0.3f, 0.8f})
	{
		m_VertexArray = TEngine::VertexArray::Create();  

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};

		TEngine::Ref<TEngine::VertexBuffer> vertexB;
		vertexB = TEngine::VertexBuffer::Create(vertices, sizeof(vertices));
		vertexB->SetLayout
		(
			{
				{ TEngine::ShaderDataType::Float3, "a_Position"},
				{ TEngine::ShaderDataType::Float2, "a_TexCoord"},
			}
		);

		m_VertexArray->AddVertexBuffer(vertexB); 

		uint32_t indices[6] = { 0, 1, 2, 1, 2, 3 };
		TEngine::Ref<TEngine::IndexBuffer> indexB;
		indexB = TEngine::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t)));  
		m_VertexArray->SetIndexBuffer(indexB);
		
		#pragma region SimpleFlatShader 

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
		
		#pragma endregion

		m_Shader = TEngine::Shader::Create("VertexPosColorTriangle", vertexSrc, fragmentSrc);
		m_TextureShader = TEngine::Shader::Create("assets/shaders/Texture.glsl");

		m_2DTexture = TEngine::Texture2D::Create("assets/textures/Logo.png");

		std::dynamic_pointer_cast<TEngine::OpenGLShader>(m_TextureShader)->Bind(); 
		std::dynamic_pointer_cast<TEngine::OpenGLShader>(m_TextureShader)->
			UploadUniformInt("u_Texture", 0);    
	}

	void OnUpdate(TEngine::Timestep ts) override 
	{
		//TE_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		m_CameraController.OnUpdate(ts); 

		#pragma region Input Test

		if (TEngine::Input::IsKeyPressed(TE_KEY_D))  
		{
			m_TrianglePosition.x += m_TriangleSpeed * ts;
		}
		if (TEngine::Input::IsKeyPressed(TE_KEY_A))    
		{
			m_TrianglePosition.x -= m_TriangleSpeed * ts;
		}

		if (TEngine::Input::IsKeyPressed(TE_KEY_S))  
		{
			m_TrianglePosition.y -= m_TriangleSpeed * ts;
		}
		if (TEngine::Input::IsKeyPressed(TE_KEY_W))  
		{
			m_TrianglePosition.y += m_TriangleSpeed * ts;
		}

		#pragma endregion

		TEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		TEngine::RenderCommand::Clear();

		TEngine::Renderer::BeginScene(m_CameraController.GetCamera());  
		 
		/*std::dynamic_pointer_cast<TEngine::OpenGLShader>(m_Shader)->
			UploadUniformFloat3("u_Color", m_TriangleColor); */

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_TrianglePosition); 

		m_2DTexture->Bind(); 
		TEngine::Renderer::Submit(m_TextureShader, m_VertexArray, transform); 

		TEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("TriangleColor", glm::value_ptr(m_TriangleColor)); 
		ImGui::End(); 
	}

	void OnEvent(TEngine::Event& e) override 
	{
		TEngine::EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<TEngine::KeyPressedEvent>(TE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent)); 
		m_CameraController.OnEvent(e); 
	}

private:

	TEngine::Ref<TEngine::Shader> m_Shader;
	TEngine::Ref<TEngine::Shader> m_TextureShader; 

	TEngine::Ref<TEngine::Texture2D> m_2DTexture;
	TEngine::Ref<TEngine::VertexArray> m_VertexArray;

	TEngine::OrthographicCameraController m_CameraController;   

	float m_TriangleSpeed = 1.0f;
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
