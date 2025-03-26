#include "tepch.h"
#include "Renderer.h"

namespace TEngine {

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& _vertexArray)
	{
		_vertexArray->Bind(); 
		RenderCommand::DrawIndexed(_vertexArray);
	}

}