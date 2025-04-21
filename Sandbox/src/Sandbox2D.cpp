#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <chrono>

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
	m_LogoTexture2D = TEngine::Texture2D::Create("assets/textures/Checkerboard.png");  
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(TEngine::Timestep ts)
{
	TE_PROFILE_FUNCTION();  

	{
		TE_PROFILE_SCOPE("CameraController::OnUpdate"); 
		m_CameraController.OnUpdate(ts);
	}

	{
		TE_PROFILE_SCOPE("Renderer Prep"); 
		TEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		TEngine::RenderCommand::Clear();
	}

	{
		TE_PROFILE_SCOPE("Renderer Draw"); 
		TEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		TEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
		TEngine::Renderer2D::DrawQuad({ 0.5f, 0.0f }, { 0.5f, 1.0f }, m_SquareColor);
		TEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_LogoTexture2D); 
		TEngine::Renderer2D::EndScene();
	}
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
