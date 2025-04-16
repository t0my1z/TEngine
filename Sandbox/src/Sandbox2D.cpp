#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include "Platforms/OpenGL/OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sandbox2D::Sandbox2D()
	: 
	Layer("Sandbox2D"),
	m_CameraController(1280.0f / 720.0f),
	m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f }) 
{
}

void Sandbox2D::OnAttach()
{
	m_VertexArray = TEngine::VertexArray::Create();

	float vertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f
	};

	TEngine::Ref<TEngine::VertexBuffer> vertexB;
	vertexB = TEngine::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexB->SetLayout
	(
		{
			{ TEngine::ShaderDataType::Float3, "a_Position"}
		}
	);

	m_VertexArray->AddVertexBuffer(vertexB);

	uint32_t indices[6] = { 0, 1, 2, 1, 2, 3 };
	TEngine::Ref<TEngine::IndexBuffer> indexB;
	indexB = TEngine::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(indexB);

	m_FlatColorShader = TEngine::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(TEngine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	
	TEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f }); 
	TEngine::RenderCommand::Clear(); 

	TEngine::Renderer::BeginScene(m_CameraController.GetCamera()); 

	std::dynamic_pointer_cast<TEngine::OpenGLShader>(m_FlatColorShader)->Bind(); 
	std::dynamic_pointer_cast<TEngine::OpenGLShader>(m_FlatColorShader)-> 
		UploadUniformFloat4("u_Color", m_SquareColor);    

	TEngine::Renderer::Submit(m_FlatColorShader, m_VertexArray, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));   

	TEngine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{ 
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("SquareColor", glm::value_ptr(m_SquareColor));    
	ImGui::End(); 
}

void Sandbox2D::OnEvent(TEngine::Event& e)
{
	m_CameraController.OnEvent(e); 
}
