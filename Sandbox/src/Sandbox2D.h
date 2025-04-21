#pragma once

#include "TEngine.h"

class Sandbox2D : public TEngine::Layer
{
public:

	Sandbox2D();
	virtual ~Sandbox2D() = default; 

	virtual void OnAttach() override;
	virtual void OnDetach() override; 

	void OnUpdate(TEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(TEngine::Event& e) override; 

private:

	TEngine::OrthographicCameraController m_CameraController;

	TEngine::Ref<TEngine::VertexArray> m_VertexArray;
	TEngine::Ref<TEngine::Shader> m_FlatColorShader;

	TEngine::Ref<TEngine::Texture2D> m_LogoTexture2D;   

	glm::vec4 m_SquareColor;   
};

