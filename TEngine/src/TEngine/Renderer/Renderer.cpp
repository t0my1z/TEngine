#include "tepch.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "Platforms/OpenGL/OpenGLShader.h"

namespace TEngine {

	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>(); 

	void Renderer::Init()
	{
		TE_PROFILE_FUNCTION();

		RenderCommand::Init(); 
		Renderer2D::Init();
;	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height); 
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	} 

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& _vertexArray,
		const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection",
			m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		_vertexArray->Bind(); 
		RenderCommand::DrawIndexed(_vertexArray);
	}

}